#!/usr/bin/env python
"""One-command behaviour check for a refactoring: baseline ref vs the working tree.

Builds the baseline (a git ref, default HEAD) in a separate worktree and the candidate
(this working tree), runs every scenario in scenarios.txt for N seeds under jitter, and
compares the per-frame state traces. Exit code 0 = no difference anywhere.

  python tools/replay_harness/verify.py --game-dir F:/gta3
  python tools/replay_harness/verify.py --game-dir F:/gta3 --base master~3 --seeds 3
  python tools/replay_harness/verify.py --game-dir F:/gta3 --quick

The baseline must already contain the harness (src/extras/harness.cpp). The worktree
(default: <repo>-verify-base next to the repo) is reused between runs, so its build is
incremental; vendor/ is copied into it once instead of cloning submodules.

Python 3.7+, standard library only. Windows, VS 2022 Build Tools (MSBUILD env var to override).
"""

import argparse
import os
import shutil
import subprocess
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.abspath(os.path.join(HERE, "..", ".."))
sys.path.insert(0, HERE)
import compare  # noqa: E402

PLATFORM = "win-amd64-librw_d3d9-oal"
EXE_REL = os.path.join("bin", PLATFORM, "Release", "re3.exe")
DEFAULT_MSBUILD = r"C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\MSBuild\Current\Bin\amd64\MSBuild.exe"


def run(cmd, cwd, quiet=True):
    proc = subprocess.run(cmd, cwd=cwd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                          universal_newlines=True, errors="replace")
    if proc.returncode != 0:
        tail = "\n".join(proc.stdout.splitlines()[-25:])
        raise RuntimeError("command failed (%d): %s\n%s" % (proc.returncode, " ".join(cmd), tail))
    if not quiet:
        print(proc.stdout)
    return proc.stdout


def build(tree, label):
    msbuild = os.environ.get("MSBUILD", DEFAULT_MSBUILD)
    t = time.time()
    run([os.path.join(tree, "premake5.exe"), "vs2019", "--with-librw"], tree)
    out = run([msbuild, os.path.join("build", "re3.sln"), "-m", "-nologo", "-v:m",
               "-p:Configuration=Release", "-p:Platform=" + PLATFORM,
               "-p:PlatformToolset=v143", "-p:WindowsTargetPlatformVersion=10.0"], tree)
    errors = [l for l in out.splitlines() if " error " in l]
    if errors:
        raise RuntimeError("%s build has errors:\n%s" % (label, "\n".join(errors[:10])))
    exe = os.path.join(tree, EXE_REL)
    print("built %s in %.0fs: %s" % (label, time.time() - t, exe))
    return exe


def prepare_worktree(wt, ref):
    if not os.path.isdir(os.path.join(wt, ".git")) and not os.path.isfile(os.path.join(wt, ".git")):
        run(["git", "worktree", "add", "--detach", wt, ref], REPO)
    else:
        run(["git", "checkout", "--detach", "--force", ref], wt)
    sha = run(["git", "rev-parse", "--short", "HEAD"], wt).strip()
    if not os.path.isdir(os.path.join(wt, "vendor", "librw", "src")):
        print("copying vendor/ into the worktree (once)")
        shutil.rmtree(os.path.join(wt, "vendor"), ignore_errors=True)
        shutil.copytree(os.path.join(REPO, "vendor"), os.path.join(wt, "vendor"),
                        ignore=shutil.ignore_patterns(".git"))
    # vendor is copied from this tree; warn if the baseline pins other submodule commits
    mine = run(["git", "ls-tree", "HEAD", "vendor/"], REPO)
    theirs = run(["git", "ls-tree", ref, "vendor/"], REPO)
    if mine != theirs:
        print("warning: %s pins different vendor/ submodule commits than HEAD; the copied vendor/ is HEAD's" % ref)
    return sha


def has_harness(exe):
    with open(exe, "rb") as f:
        return b"-harness-seed=" in f.read()


def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("--game-dir", required=True, help="GTA III PC install prepared for the harness (see README)")
    p.add_argument("--base", default="HEAD", help="baseline git ref (default HEAD)")
    p.add_argument("--worktree", default=os.path.join(os.path.dirname(REPO), os.path.basename(REPO) + "-verify-base"),
                   help="where the baseline is checked out and built")
    p.add_argument("--baseline-exe", help="use this baseline re3.exe instead of building --base")
    p.add_argument("--candidate-exe", help="use this candidate re3.exe instead of building the working tree")
    p.add_argument("--scenarios", default=os.path.join(HERE, "scenarios.txt"))
    p.add_argument("--seeds", type=int, default=2)
    p.add_argument("--frames", type=int, default=2000)
    p.add_argument("--jitter", type=int, default=3)
    p.add_argument("--quick", action="store_true", help="1 seed x 1000 frames per scenario")
    p.add_argument("--out", default=os.path.join(REPO, "build", "verify_out"))
    p.add_argument("--keep-going", action="store_true", help="run every scenario even after a difference")
    args = p.parse_args()
    if args.quick:
        args.seeds, args.frames = 1, 1000

    start = time.time()
    try:
        if args.baseline_exe:
            base_exe, base_desc = os.path.abspath(args.baseline_exe), args.baseline_exe
        else:
            sha = prepare_worktree(args.worktree, args.base)
            base_exe, base_desc = build(args.worktree, "baseline %s (%s)" % (args.base, sha)), "%s (%s)" % (args.base, sha)
        cand_exe = os.path.abspath(args.candidate_exe) if args.candidate_exe else build(REPO, "candidate (working tree)")
    except RuntimeError as e:
        print("ERROR:", e)
        return 2
    for label, exe in (("baseline", base_exe), ("candidate", cand_exe)):
        if not has_harness(exe):
            print("ERROR: the %s executable has no replay harness: %s" % (label, exe))
            return 2

    game_dir = os.path.abspath(args.game_dir)
    exe_a = os.path.join(game_dir, "re3_verify_baseline.exe")
    exe_b = os.path.join(game_dir, "re3_verify_candidate.exe")
    shutil.copyfile(base_exe, exe_a)
    shutil.copyfile(cand_exe, exe_b)

    scenarios = [l.strip() for l in open(args.scenarios) if l.strip() and not l.startswith("#")]
    print("baseline %s vs working tree: %d scenarios x %d seeds x %d frames, jitter %d ms"
          % (base_desc, len(scenarios), args.seeds, args.frames, args.jitter))
    failures = []
    for k, sc in enumerate(scenarios, 1):
        scenario = None if sc == "newgame" else sc
        for seed in range(1, args.seeds + 1):
            out = os.path.join(os.path.abspath(args.out), "s%d_seed%d" % (k, seed))
            os.makedirs(out, exist_ok=True)
            ta, tb = os.path.join(out, "baseline.csv"), os.path.join(out, "candidate.csv")
            ca, _ = compare.run_build(exe_a, game_dir, seed, args.frames, ta, 0, False, 900, scenario, False, args.jitter)
            cb, _ = compare.run_build(exe_b, game_dir, seed, args.frames, tb, 0, False, 900, scenario, False, args.jitter)
            status, msg = compare.compare(ta, tb)
            if ca == "timeout" or cb == "timeout":
                status, msg = "error", msg + " (timeout)"
            print("  %-60s seed %d: %s - %s" % (sc[:60], seed, status.upper(), msg))
            sys.stdout.flush()
            if status != "ok":
                failures.append((sc, seed, status, msg, out))
                if not args.keep_going:
                    break
        if failures and not args.keep_going:
            break

    print("%.0f s" % (time.time() - start))
    if not failures:
        print("PASS: no behaviour difference in any scenario")
        return 0
    sc, seed, status, msg, out = failures[0]
    print("FAIL: %s, seed %d: %s" % (sc, seed, msg))
    print("traces: %s" % out)
    detail = "" if sc == "newgame" else " --scenario %s" % sc
    print("to see which variable diverged, rerun that seed with per-frame detail logs:")
    print("  python tools/replay_harness/compare.py %s %s --game-dir %s --seed %d --seeds 1 --frames %d --jitter %d%s --detail --out %s"
          % (exe_a, exe_b, args.game_dir, seed, args.frames, args.jitter, detail, os.path.join(out, "detail")))
    return 1


if __name__ == "__main__":
    sys.exit(main())
