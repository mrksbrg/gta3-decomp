#!/usr/bin/env python
"""Run two re3 builds through the replay harness and compare their state traces.

Each seed is one run of N frames per build. Both builds get identical harness
arguments; a behaviour-preserving change must produce byte-identical traces.
For each seed the script reports either OK or the first frame where the traces
differ and which state components (peds, vehicles, script, ...) differ there.

Examples:
  # determinism self-check: the same build twice
  python tools/replay_harness/compare.py re3.exe re3.exe --game-dir F:/gta3 --seeds 3

  # baseline vs candidate
  python tools/replay_harness/compare.py base/re3.exe bin/.../re3.exe --game-dir F:/gta3 --seeds 10 --frames 6000

Exit code: 0 when every seed matches, 1 when any seed differs or a run fails.
Python 3.7+, standard library only.
"""

import argparse
import os
import shutil
import subprocess
import sys
import time

# OpenAL's no-output backend: the harness hashes audio requests and emulates playback in
# game time, so a real sound device only adds machine dependence (and the Windows default
# device can take a minute to open). It must be in the environment at process start.
GAME_ENV = dict(os.environ, ALSOFT_DRIVERS="null")

COMPONENTS = ["time_ms", "rng", "peds", "vehicles", "objects", "player", "script", "camera", "world", "audio", "draw2d"]


def read_trace(path):
    """Returns (status, header, rows). status is 'complete', 'crash' or 'incomplete'."""
    header = None
    status = "incomplete"
    rows = []
    with open(path, "r") as f:
        for line in f:
            line = line.rstrip("\n")
            if not line:
                continue
            if line.startswith("#"):
                if line.startswith("# end frames="):
                    status = "complete"
                elif line.startswith("# crash:"):
                    status = "crash"
                continue
            if header is None:
                header = line.split(",")
                continue
            rows.append(line.split(","))
    return status, header, rows


def run_build(exe_in_game_dir, game_dir, seed, frames, trace_path, load_slot, idle, timeout, scenario=None, detail=False, jitter=0):
    args = [exe_in_game_dir, "-harness", "-harness-seed=%d" % seed, "-harness-frames=%d" % frames,
            "-harness-trace=%s" % trace_path]
    if load_slot:
        args.append("-harness-load=%d" % load_slot)
    if idle:
        args.append("-harness-idle")
    if scenario:
        args.append("-harness-scenario=%s" % scenario)
    if detail:
        args.append("-harness-detail")
    if jitter:
        args.append("-harness-jitter=%d" % jitter)
    if os.path.exists(trace_path):
        os.remove(trace_path)
    start = time.time()
    try:
        proc = subprocess.run(args, cwd=game_dir, timeout=timeout, env=GAME_ENV)
        code = proc.returncode
    except subprocess.TimeoutExpired:
        code = "timeout"
    return code, time.time() - start


def compare(trace_a, trace_b):
    """Returns (status, message). status is 'ok', 'diff' or 'error'."""
    if not os.path.exists(trace_a) or not os.path.exists(trace_b):
        return "error", "missing trace (%s exists: %s, %s exists: %s)" % (
            trace_a, os.path.exists(trace_a), trace_b, os.path.exists(trace_b))
    end_a, header_a, rows_a = read_trace(trace_a)
    end_b, header_b, rows_b = read_trace(trace_b)
    if header_a != header_b:
        return "error", "trace headers differ"
    if end_a != "complete" or end_b != "complete":
        # a run that crashed or stopped early can still match up to where it ended
        return "error", "run did not finish (baseline %s, candidate %s; %d / %d frames)" % (
            end_a, end_b, len(rows_a), len(rows_b))
    col = {name: i for i, name in enumerate(header_a)}
    for i in range(min(len(rows_a), len(rows_b))):
        ra, rb = rows_a[i], rows_b[i]
        if ra != rb:
            differing = [c for c in COMPONENTS if ra[col[c]] != rb[col[c]]]
            where = "player at (%s, %s, %s)" % (ra[col["px"]], ra[col["py"]], ra[col["pz"]])
            return "diff", "first difference at frame %s: %s; %s" % (
                ra[col["frame"]], ", ".join(differing) or "counts/position only", where)
    if len(rows_a) != len(rows_b):
        return "diff", "traces match for %d frames, then lengths differ (%d vs %d frames)" % (
            min(len(rows_a), len(rows_b)), len(rows_a), len(rows_b))
    return "ok", "%d frames identical" % len(rows_a)


def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("baseline", help="baseline re3.exe")
    p.add_argument("candidate", help="candidate re3.exe (may be the same file for a determinism check)")
    p.add_argument("--game-dir", required=True, help="GTA III PC install with re3 gamefiles copied in")
    p.add_argument("--seed", type=int, default=1, help="first seed (default 1)")
    p.add_argument("--seeds", type=int, default=3, help="number of seeds (default 3)")
    p.add_argument("--frames", type=int, default=3000, help="frames per run (default 3000, 60 s of game time)")
    p.add_argument("--load", type=int, default=0, help="save slot to start from (1-8), default new game")
    p.add_argument("--idle", action="store_true", help="send no input")
    p.add_argument("--scenario", help="scenario modifiers, e.g. freeroam,armed,wanted=4,car=taxi,at=staunton")
    p.add_argument("--jitter", type=int, default=0, help="random sleeps of up to N ms per frame point, to expose timing dependence")
    p.add_argument("--detail", action="store_true", help="also write per-frame detail logs (slower)")
    p.add_argument("--out", default="harness_out", help="directory for traces (default harness_out)")
    p.add_argument("--timeout", type=int, default=900, help="seconds per run before it counts as hung")
    args = p.parse_args()

    game_dir = os.path.abspath(args.game_dir)
    out = os.path.abspath(args.out)
    os.makedirs(out, exist_ok=True)

    # re3 finds its data and DLLs relative to the game folder, so run copies from there.
    exe_a = os.path.join(game_dir, "re3_harness_baseline.exe")
    exe_b = os.path.join(game_dir, "re3_harness_candidate.exe")
    shutil.copyfile(args.baseline, exe_a)
    shutil.copyfile(args.candidate, exe_b)

    failures = 0
    for seed in range(args.seed, args.seed + args.seeds):
        trace_a = os.path.join(out, "seed%d_baseline.csv" % seed)
        trace_b = os.path.join(out, "seed%d_candidate.csv" % seed)
        code_a, t_a = run_build(exe_a, game_dir, seed, args.frames, trace_a, args.load, args.idle, args.timeout, args.scenario, args.detail, args.jitter)
        code_b, t_b = run_build(exe_b, game_dir, seed, args.frames, trace_b, args.load, args.idle, args.timeout, args.scenario, args.detail, args.jitter)
        status, msg = compare(trace_a, trace_b)
        if code_a != 0 or code_b != 0:
            # re3 sometimes exits with 1 at shutdown after a finished run; the trace's end
            # marker decides, the exit code is only reported
            msg += " (exit codes %s / %s)" % (code_a, code_b)
            if code_a == "timeout" or code_b == "timeout":
                status = "error"
        if status != "ok":
            failures += 1
        print("seed %d: %s - %s [%.0fs + %.0fs]" % (seed, status.upper(), msg, t_a, t_b))
        sys.stdout.flush()

    print("%d of %d seeds match" % (args.seeds - failures, args.seeds))
    return 0 if failures == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
