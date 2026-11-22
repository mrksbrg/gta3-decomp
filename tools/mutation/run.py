#!/usr/bin/env python
"""Mutation testing of re3 against the replay harness (Mull profile, Windows).

    python tools/mutation/run.py --game-dir F:/gta3 --cov-dir F:/gta3/harness_out/cov19 \\
        --files src/peds/PedFight.cpp src/peds/Ped.cpp --sample 150 --out build/mutation/run1
    python tools/mutation/run.py ... --sample 0 --lanes 4      # every mutant, four in parallel
    python tools/mutation/run.py --out build/mutation/run1 --report-only

For each target file the Mull-profile mutants are enumerated (mutants.py) and a seeded
sample of --sample is drawn (0 = all). Mutants on lines that no harness run executes are
recorded as "no_coverage" without building. Every other mutant is applied to the source,
the game is rebuilt incrementally, the source is restored at once, and the mutant runs
the harness runs (scenario x seed, from coverage_run.sh's per-run profiles) that execute
its line, each with -harness-expect=<baseline trace>, which stops at the first differing
frame. The first run that diverges, crashes, ends early or times out kills the mutant;
if none does, it survived. Results are appended to results*.jsonl, so an interrupted run
resumes where it stopped. If a runner dies while a mutant is applied, the next start
restores the file from its pending*.json.

Lanes (--lanes N): the coordinator records the baselines once, then makes N copies of the
source tree next to the repo (<repo>-mutlane<k>: src, res, vendor, premake; copies, not
git worktrees, so the files stay byte-identical to the ones the mutants were enumerated
from), builds each, and starts N worker processes. Worker k takes every N-th mutant and
has its own build, game executable (re3_mutant_lane<k>.exe), user-files folder, results
file (results_lane<k>.jsonl) and restore file. Before it starts, each worker runs its
clean build against one baseline and stops if that does not match exactly. Mutants are
only ever applied in the lane copies, never in the repo.

Scores as in the Jellyfin and ImageMagick reports:
    score     killed / (killed + survived + no_coverage)
    covered   killed / (killed + survived)
Timeouts and crashes count as killed; compile errors are left out. Function verdicts use
the ImageMagick gate: ready >= 90%, careful 75-90%, not ready < 75% (covered score, at
least 5 mutants).

Python 3.7+, standard library only. Needs the coverage build's per-run profiles
(coverage_run.sh with scenarios.txt) and MSYS2 LLVM for llvm-profdata / llvm-cov.
"""

import argparse
import collections
import glob
import json
import os
import random
import re
import shutil
import subprocess
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.abspath(os.path.join(HERE, "..", ".."))
sys.path.insert(0, HERE)
import mutants as mutgen  # noqa: E402

# OpenAL's no-output backend: the harness hashes audio requests and emulates playback in
# game time, so a real sound device only adds machine dependence (and the Windows default
# device can take a minute to open). It must be in the environment at process start.
GAME_ENV = dict(os.environ, ALSOFT_DRIVERS="null")

PLATFORM = "win-amd64-librw_d3d9-oal"
COV_EXE = os.path.join(REPO, "bin", "coverage", "re3.exe")
LLVM = r"C:\msys64\mingw64\bin"
DEFAULT_MSBUILD = r"C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\MSBuild\Current\Bin\amd64\MSBuild.exe"


def exe_of(tree):
    return os.path.join(tree, "bin", PLATFORM, "Release", "re3.exe")


def msbuild(tree):
    proc = subprocess.run([os.environ.get("MSBUILD", DEFAULT_MSBUILD), os.path.join("build", "re3.sln"), "-m",
                           "-nologo", "-v:m", "-p:Configuration=Release", "-p:Platform=" + PLATFORM,
                           "-p:PlatformToolset=v143", "-p:WindowsTargetPlatformVersion=10.0"],
                          cwd=tree, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, universal_newlines=True,
                          errors="replace")
    errors = [l for l in proc.stdout.splitlines() if " error " in l]
    return proc.returncode == 0 and not errors, errors


# ---------------------------------------------------------------------------
# which harness runs execute which lines

def line_coverage(cov_dir, files, cache):
    """{file: {line: [(scenario_index, seed), ...]}} from the per-run profiles."""
    if os.path.exists(cache):
        data = json.load(open(cache))
        if all(f in data["files"] for f in files):
            return data["runs"], {f: {int(l): [tuple(r) for r in v] for l, v in data["files"][f].items()} for f in files}
    scenarios = [l.strip() for l in open(os.path.join(cov_dir, "scenarios.list")) if l.strip()]
    runs = []
    for name in sorted(os.listdir(cov_dir)):
        m = re.match(r"run_s(\d+)_seed(\d+)\.profraw$", name)
        if m:
            runs.append((int(m.group(1)), int(m.group(2))))
    runs.sort()
    cover = {f: collections.defaultdict(list) for f in files}
    abs_files = {os.path.normcase(os.path.join(REPO, f)).replace("\\", "/"): f for f in files}
    for k, seed in runs:
        prof = os.path.join(cov_dir, "run_s%d_seed%d.profdata" % (k, seed))
        if not os.path.exists(prof):
            subprocess.run([os.path.join(LLVM, "llvm-profdata.exe"), "merge", "-sparse",
                            os.path.join(cov_dir, "run_s%d_seed%d.profraw" % (k, seed)), "-o", prof], check=True)
        out = subprocess.run([os.path.join(LLVM, "llvm-cov.exe"), "show", COV_EXE, "-instr-profile=" + prof]
                             + [os.path.join(REPO, f) for f in files],
                             stdout=subprocess.PIPE, universal_newlines=True, errors="replace", check=True).stdout
        # with a single file llvm-cov prints no "<path>:" header line
        current = files[0] if len(files) == 1 else None
        for line in out.splitlines():
            if line.endswith(":") and not line.startswith(" "):
                current = abs_files.get(os.path.normcase(line[:-1]).replace("\\", "/"))
                continue
            m = re.match(r"\s*(\d+)\|\s*([0-9.]+[kMGE]?)\|", line)
            if current and m and m.group(2) not in ("0",):
                cover[current][int(m.group(1))].append((k, seed))
    data = {"runs": {str(k): scenarios[k - 1] for k, _ in runs},
            "files": {f: {str(l): v for l, v in cover[f].items()} for f in files}}
    json.dump(data, open(cache, "w"))
    return data["runs"], {f: dict(cover[f]) for f in files}


# ---------------------------------------------------------------------------
# harness runs

def harness_args(scenario, seed, frames, trace, expect=None, userfiles="mutation"):
    args = ["-harness", "-harness-seed=%d" % seed, "-harness-frames=%d" % frames, "-harness-trace=" + trace,
            "-harness-userfiles=harness_userfiles/" + userfiles]  # one empty folder per runner
    if scenario and scenario != "newgame":
        args.append("-harness-scenario=" + scenario)
    if expect:
        args.append("-harness-expect=" + expect)
    return args


def run_game(exe, game_dir, args, timeout):
    start = time.time()
    try:
        subprocess.run([exe] + args, cwd=game_dir, timeout=timeout, env=GAME_ENV,
                       stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        timed_out = False
    except subprocess.TimeoutExpired:
        subprocess.run(["taskkill", "/F", "/IM", os.path.basename(exe)], stdout=subprocess.DEVNULL,
                       stderr=subprocess.DEVNULL)
        timed_out = True
    return timed_out, time.time() - start


def trace_outcome(path):
    """'same', 'diverged:<frame>', 'crash' or 'incomplete'."""
    if not os.path.exists(path):
        return "incomplete"
    text = open(path, errors="replace").read()
    m = re.search(r"^# diverged at frame (\d+)", text, re.M)
    if m:
        return "diverged:" + m.group(1)
    if "\n# crash:" in text:
        return "crash"
    if "\n# end frames=" in text:
        return "same"
    return "incomplete"


# ---------------------------------------------------------------------------
# applying mutants (always restored)

def apply_mutant(tree, m, pending_path):
    path = os.path.join(tree, m["file"])
    original = open(path, "rb").read()
    json.dump({"file": path, "backup": path + ".mutation-backup"}, open(pending_path, "w"))
    shutil.copyfile(path, path + ".mutation-backup")
    o, n = m["offset"], m["length"]
    assert original[o:o + n].decode("latin-1") == m["original"], "source changed since enumeration: " + m["id"]
    open(path, "wb").write(original[:o] + m["replacement"].encode("latin-1") + original[o + n:])
    return path, original


def restore(path, original, pending_path):
    open(path, "wb").write(original)
    for p in (path + ".mutation-backup", pending_path):
        if os.path.exists(p):
            os.remove(p)


def recover(pending_path):
    if os.path.exists(pending_path):
        info = json.load(open(pending_path))
        if os.path.exists(info["backup"]):
            shutil.copyfile(info["backup"], info["file"])
            os.remove(info["backup"])
            print("restored %s from an interrupted run" % info["file"])
        os.remove(pending_path)


# ---------------------------------------------------------------------------
# lanes

def lane_dir(k):
    return os.path.join(os.path.dirname(REPO), os.path.basename(REPO) + "-mutlane%d" % k)


def prepare_lane(k):
    """A byte-identical copy of the source tree with its own build."""
    lane = lane_dir(k)
    os.makedirs(lane, exist_ok=True)
    for d in ("src", "res", "autoconf"):
        shutil.rmtree(os.path.join(lane, d), ignore_errors=True)
        shutil.copytree(os.path.join(REPO, d), os.path.join(lane, d))
    if not os.path.isdir(os.path.join(lane, "vendor", "librw", "src")):
        shutil.rmtree(os.path.join(lane, "vendor"), ignore_errors=True)
        shutil.copytree(os.path.join(REPO, "vendor"), os.path.join(lane, "vendor"), ignore=shutil.ignore_patterns(".git"))
    for f in ("premake5.exe", "premake5.lua"):
        shutil.copyfile(os.path.join(REPO, f), os.path.join(lane, f))
    # the copy has no .git: keep the repo's version file instead of asking git for one
    shutil.copyfile(os.path.join(REPO, "src", "extras", "GitSHA1.cpp"), os.path.join(lane, "GitSHA1.fixed"))
    with open(os.path.join(lane, "printHash.bat"), "w") as f:
        f.write('@copy /y "%~dp0GitSHA1.fixed" %1 >nul\n')
    subprocess.run([os.path.join(lane, "premake5.exe"), "vs2019", "--with-librw"], cwd=lane, check=True,
                   stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    ok, errors = msbuild(lane)
    if not ok:
        raise RuntimeError("lane %d build failed: %s" % (k, errors[:3]))
    return lane


def results_files(out):
    return sorted(glob.glob(os.path.join(out, "results*.jsonl")))


def load_results(out):
    rs = []
    for p in results_files(out):
        rs += [json.loads(l) for l in open(p)]
    return rs


# ---------------------------------------------------------------------------
# report

def verdict(covered, n):
    if n < 5:
        return "too few"
    return "ready" if covered >= 0.9 else "careful" if covered >= 0.75 else "not ready"


def report(out):
    results = load_results(out)
    lines = ["# Mutation results (Mull profile: cxx_default + cxx_remove_void_call)", ""]

    def row(rs):
        c = collections.Counter(r["status"] for r in rs)
        killed, survived, nocov = c["killed"], c["survived"], c["no_coverage"]
        total = killed + survived + nocov
        score = killed / total if total else 0.0
        cov = killed / (killed + survived) if killed + survived else 0.0
        return killed, survived, nocov, c["compile_error"], score, cov

    lines += ["| File | Killed | Survived | No coverage | Compile errors | Score | Covered score |",
              "| --- | --- | --- | --- | --- | --- | --- |"]
    by_file = collections.defaultdict(list)
    for r in results:
        by_file[r["file"]].append(r)
    for f in sorted(by_file):
        k, s, nc, ce, sc, cv = row(by_file[f])
        lines.append("| %s | %d | %d | %d | %d | %.1f%% | %.1f%% |" % (f, k, s, nc, ce, 100 * sc, 100 * cv))
    k, s, nc, ce, sc, cv = row(results)
    lines.append("| **all** | %d | %d | %d | %d | **%.1f%%** | **%.1f%%** |" % (k, s, nc, ce, 100 * sc, 100 * cv))
    lines += ["", "## Functions (covered score; ImageMagick gate: ready >= 90%, careful 75-90%, not ready < 75%)", "",
              "| File | Function | Killed | Survived | No coverage | Covered score | Verdict |",
              "| --- | --- | --- | --- | --- | --- | --- |"]
    by_func = collections.defaultdict(list)
    for r in results:
        by_func[(r["file"], r["function"])].append(r)
    for (f, fn), rs in sorted(by_func.items(), key=lambda x: (x[0][0], -len(x[1]))):
        k, s, nc, ce, sc, cv = row(rs)
        lines.append("| %s | %s | %d | %d | %d | %.0f%% | %s |" % (os.path.basename(f), fn, k, s, nc, 100 * cv,
                                                                  verdict(cv, k + s)))
    ops = collections.defaultdict(list)
    for r in results:
        ops[r["op"]].append(r)
    lines += ["", "## Operators", "", "| Operator | Killed | Survived | No coverage | Covered score |",
              "| --- | --- | --- | --- | --- |"]
    for op, rs in sorted(ops.items(), key=lambda x: -len(x[1])):
        k, s, nc, ce, sc, cv = row(rs)
        lines.append("| %s | %d | %d | %d | %.0f%% |" % (op, k, s, nc, 100 * cv))
    surv = [r for r in results if r["status"] == "survived"]
    lines += ["", "## Survivors (first 60)", ""]
    for r in surv[:60]:
        lines.append("- %s:%d %s `%s` -> `%s` (%s)" % (r["file"], r["line"], r["function"], r["original"][:60],
                                                      r["replacement"], r["op"]))
    text = "\n".join(lines) + "\n"
    open(os.path.join(out, "report.md"), "w").write(text)
    return text


# ---------------------------------------------------------------------------

def build_plan(args, out, files):
    plan = []
    for f in files:
        cache = os.path.join(out, "mutants_%s.json" % os.path.basename(f))
        if not os.path.exists(cache):
            json.dump(mutgen.enumerate_mutants(os.path.join(REPO, f)), open(cache, "w"))
        ms = json.load(open(cache))
        # seeded shuffle, then the first N: a larger --sample always contains a smaller one
        shuffled = list(ms)
        random.Random("%d:%s" % (args.seed, f)).shuffle(shuffled)
        sample = shuffled if args.sample <= 0 else shuffled[:args.sample]
        for rank, m in enumerate(sample):
            m["rank"] = rank
        if args.lane is None:
            print("%s: %d mutants, %d sampled" % (f, len(ms), len(sample)))
        plan += sample
    # interleave the files by rank, so a time budget leaves every file with the same count
    plan.sort(key=lambda m: (m["rank"], files.index(m["file"])))
    if args.only_survivors_of:
        keep = {json.loads(l)["id"] for l in open(args.only_survivors_of) if json.loads(l)["status"] == "survived"}
        plan = [m for m in plan if m["id"] in keep]
    if args.only_ids:
        keep = {l.strip() for l in open(args.only_ids) if l.strip()}
        plan = [m for m in plan if m["id"] in keep]
    if args.retest_of:
        earlier = [json.loads(l) for l in open(args.retest_of)]
        again = {r["id"] for r in earlier if r["status"] in ("survived", "no_coverage")}
        plan = [m for m in plan if m["id"] in again]
        first = os.path.join(out, "results_earlier.jsonl")
        if args.lane is None and not os.path.exists(first):
            with open(first, "w") as f:
                for r in earlier:
                    if r["status"] in ("killed", "compile_error"):
                        r = dict(r)
                        r["by"] = (r["by"] or "") + " (earlier run)"
                        f.write(json.dumps(r) + "\n")
    return plan


def baselines(args, out, plan, cover, runs_desc, lo, hi, exe):
    needed = sorted({r for m in plan for r in cover[m["file"]].get(m["line"], [])[lo:hi]})
    base_dir = os.path.join(out, "baselines")
    os.makedirs(base_dir, exist_ok=True)
    base_time = {}
    game_exe = os.path.join(args.game_dir, "re3_mutant_base.exe")
    if exe:
        shutil.copyfile(exe, game_exe)
    for k, seed in needed:
        trace = os.path.join(base_dir, "s%d_seed%d.csv" % (k, seed))
        tfile = trace + ".time"
        if not (os.path.exists(trace) and trace_outcome(trace) == "same" and os.path.exists(tfile)):
            if not exe:
                continue  # workers only use what the coordinator recorded
            _, t = run_game(game_exe, args.game_dir, harness_args(runs_desc[str(k)], seed, args.frames, trace), 600)
            if trace_outcome(trace) != "same":
                print("baseline run s%d seed %d did not finish; its mutants will be skipped" % (k, seed))
                continue
            open(tfile, "w").write("%.1f" % t)
        base_time[(k, seed)] = float(open(tfile).read())
    return base_dir, base_time


def worker(args, out, files, plan, cover, runs_desc, lo, hi, base_dir, base_time, tree, tag):
    """Runs the plan in one source tree. tag names its exe, files and folders."""
    pending = os.path.join(out, "pending%s.json" % tag)
    recover(pending)
    results_path = os.path.join(out, "results%s.jsonl" % tag)
    done = set()
    for p in results_files(out):
        done |= {json.loads(l)["id"] for l in open(p)}
    exe = exe_of(tree)
    game_exe = os.path.join(args.game_dir, "re3_mutant%s.exe" % tag)
    userfiles = "mutation%s" % tag
    last = os.path.join(out, "last_mutant%s.csv" % tag)
    ok, errors = msbuild(tree)  # clean, unmutated
    if not ok:
        print("clean build failed in %s: %s" % (tree, errors[:3]))
        return 2
    if args.lane is not None and base_time:
        # this tree's clean build must reproduce a baseline exactly
        shutil.copyfile(exe, game_exe)
        (k, seed) = sorted(base_time)[0]
        if os.path.exists(last):
            os.remove(last)
        run_game(game_exe, args.game_dir, harness_args(runs_desc[str(k)], seed, args.frames, last,
                                                       os.path.join(base_dir, "s%d_seed%d.csv" % (k, seed)), userfiles),
                 6 * base_time[(k, seed)] + 60)
        if trace_outcome(last) != "same":
            print("lane%s: clean build does not reproduce baseline s%d seed %d (%s); stopping"
                  % (tag, k, seed, trace_outcome(last)))
            return 3
        print("lane%s: clean build reproduces baseline s%d seed %d" % (tag, k, seed))

    start = time.time()
    todo = [m for m in plan if m["id"] not in done]
    print("%s%d mutants to run" % ("lane%s: " % tag if tag else "", len(todo)))
    for i, m in enumerate(todo, 1):
        if args.hours and time.time() - start > args.hours * 3600:
            print("time budget reached")
            break
        runs = [r for r in cover[m["file"]].get(m["line"], [])[lo:hi] if r in base_time]
        rec = dict(m)
        rec.update(status=None, by=None, runs=[list(r) for r in runs], seconds=0)
        t0 = time.time()
        if not runs and args.only_survivors_of:
            rec["status"] = "survived"
            rec["by"] = "no further covering runs"
        elif not runs:
            rec["status"] = "no_coverage"
        else:
            path, original = apply_mutant(tree, m, pending)
            try:
                ok, errors = msbuild(tree)
            finally:
                restore(path, original, pending)
            if not ok:
                rec["status"] = "compile_error"
                rec["by"] = errors[0][:200] if errors else "build failed"
            else:
                shutil.copyfile(exe, game_exe)
                rec["status"] = "survived"
                for k, seed in runs:
                    if os.path.exists(last):
                        os.remove(last)
                    expect = os.path.join(base_dir, "s%d_seed%d.csv" % (k, seed))
                    # generous: with several lanes the machine is busy, and a slow run must not
                    # pass for a hang
                    timed_out, _ = run_game(game_exe, args.game_dir,
                                            harness_args(runs_desc[str(k)], seed, args.frames, last, expect, userfiles),
                                            6 * base_time[(k, seed)] + 60)
                    outcome = "timeout" if timed_out else trace_outcome(last)
                    if outcome != "same":
                        rec["status"] = "killed"
                        rec["by"] = "s%d seed %d: %s" % (k, seed, outcome)
                        break
        rec["seconds"] = round(time.time() - t0, 1)
        with open(results_path, "a") as f:
            f.write(json.dumps(rec) + "\n")
        print("%s[%d/%d] %s %s:%d %s -> %s (%.0fs)" % ("lane%s " % tag if tag else "", i, len(todo), rec["status"],
                                                       m["file"], m["line"], m["op"], rec["by"] or "", rec["seconds"]))
        sys.stdout.flush()
    msbuild(tree)  # leave a clean, unmutated build behind
    return 0


def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("--game-dir")
    p.add_argument("--cov-dir", help="coverage_run.sh output with run_s<K>_seed<N>.profraw and scenarios.list")
    p.add_argument("--files", nargs="+", default=[])
    p.add_argument("--sample", type=int, default=150, help="mutants per file (0 = all)")
    p.add_argument("--seed", type=int, default=1, help="sampling seed")
    p.add_argument("--frames", type=int, default=3000, help="must match the coverage runs")
    p.add_argument("--max-runs", type=int, default=6, help="covering harness runs tried per mutant")
    p.add_argument("--out", required=True)
    p.add_argument("--report-only", action="store_true")
    p.add_argument("--lanes", type=int, default=1, help="parallel lanes (copies of the source tree)")
    p.add_argument("--lane", type=int, help=argparse.SUPPRESS)  # worker: index of this lane
    p.add_argument("--only-survivors-of", help="results.jsonl of an earlier run: rerun only its survivors")
    p.add_argument("--retest-of", help="results.jsonl of an earlier run: rerun its survivors and no-coverage "
                   "mutants (after harness or scenario changes); its kills are copied over unchanged")
    p.add_argument("--only-ids", help="a file with one mutant id per line: run only these")
    p.add_argument("--run-offset", type=int, default=0,
                   help="skip the first N covering runs of each mutant (with --only-survivors-of: the ones already tried)")
    p.add_argument("--hours", type=float, default=0, help="stop after this many hours (0 = no limit)")
    args = p.parse_args()
    out = os.path.abspath(args.out)
    os.makedirs(out, exist_ok=True)
    if args.report_only:
        print(report(out))
        return 0

    files = [f.replace("\\", "/") for f in args.files]
    plan = build_plan(args, out, files)
    lo, hi = args.run_offset, args.run_offset + args.max_runs
    runs_desc, cover = line_coverage(args.cov_dir, files, os.path.join(out, "coverage_map.json"))

    if args.lane is not None:  # a worker started by the coordinator
        base_dir, base_time = baselines(args, out, plan, cover, runs_desc, lo, hi, None)
        mine = [m for i, m in enumerate(plan) if i % args.lanes == args.lane]
        return worker(args, out, files, mine, cover, runs_desc, lo, hi, base_dir, base_time,
                      lane_dir(args.lane), "_lane%d" % args.lane)

    # coordinator: an unmutated build of the repo records the baselines
    ok, errors = msbuild(REPO)
    if not ok:
        print("baseline build failed:\n" + "\n".join(errors))
        return 2
    base_dir, base_time = baselines(args, out, plan, cover, runs_desc, lo, hi, exe_of(REPO))
    print("%d baseline runs ready" % len(base_time))

    if args.lanes <= 1:
        rc = worker(args, out, files, plan, cover, runs_desc, lo, hi, base_dir, base_time, REPO, "")
    else:
        procs = []
        for k in range(args.lanes):
            t = time.time()
            lane = prepare_lane(k)
            for f in files:  # mutant offsets must match these bytes exactly
                assert open(os.path.join(lane, f), "rb").read() == open(os.path.join(REPO, f), "rb").read(), f
            print("lane %d ready in %.0fs: %s" % (k, time.time() - t, lane))
            log = open(os.path.join(out, "lane%d.log" % k), "a")
            cmd = [sys.executable, "-u", os.path.abspath(__file__)] + sys.argv[1:] + ["--lane", str(k)]
            procs.append((subprocess.Popen(cmd, stdout=log, stderr=subprocess.STDOUT), log))
            sys.stdout.flush()
        rc = 0
        for proc, log in procs:
            rc |= proc.wait()
            log.close()
        print("all lanes finished (exit codes combined: %d)" % rc)
    # the environment can drift during a long run: every kill relies on the baselines, so
    # check at the end that the clean build still reproduces each one
    ok, _ = msbuild(REPO)
    drift = []
    game_exe = os.path.join(args.game_dir, "re3_mutant_base.exe")
    shutil.copyfile(exe_of(REPO), game_exe)
    for (k, seed) in sorted(base_time):
        last = os.path.join(out, "last_baseline_check.csv")
        if os.path.exists(last):
            os.remove(last)
        run_game(game_exe, args.game_dir, harness_args(runs_desc[str(k)], seed, args.frames, last,
                                                       os.path.join(base_dir, "s%d_seed%d.csv" % (k, seed))), 600)
        if trace_outcome(last) != "same":
            drift.append("s%d seed %d: %s" % (k, seed, trace_outcome(last)))
    json.dump(drift, open(os.path.join(out, "baseline_drift.json"), "w"))
    print("baseline check at the end: %d of %d not reproduced%s" % (len(drift), len(base_time),
                                                                   (": " + "; ".join(drift)) if drift else ""))
    print(report(out))
    return rc


if __name__ == "__main__":
    sys.exit(main())
