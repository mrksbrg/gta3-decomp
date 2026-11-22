# Mutation testing (Mull profile, Windows)

Measures how well the replay harness (`tools/replay_harness/`) detects behaviour changes,
with the operator set used for the ImageMagick and 3SX campaigns and reported for
Jellyfin: Mull's `cxx_default` plus `cxx_remove_void_call`. Mull itself only runs on
Linux and the harness only on Windows, so this is a source-level re-implementation of
that profile, not Mull: counts are close to Mull's but not identical (Mull mutates LLVM
IR and also sees operators the front end introduces).

## Pieces

- `mutants.py FILE` lists the mutants of one source file from clang's JSON AST (MSYS2
  `clang-cl`, include paths and defines from `build/re3.vcxproj`): equality, relational
  and boundary, arithmetic, increment (`++` to `--`), unary minus, and void-call removal.
  This is exactly the set mull-runner 0.34.1 generates for `cxx_default` +
  `cxx_remove_void_call` on a test file (checked in WSL, 2026-11-21): `cxx_default` has no
  compound assignment (`+=` etc.) and no decrement (`--` to `++`). Nothing inside macro expansions or headers, nothing in inactive
  `#ifdef` branches, no operators on pure literals (the compiler folds those, so Mull
  never sees them). Each mutant is a byte range and a replacement, with file, line and
  enclosing function.
- `run.py` samples mutants per file, maps every line to the harness runs (scenario x
  seed) that execute it using the per-run coverage profiles of
  `tools/replay_harness/coverage_run.sh`, records one baseline trace per needed run, then
  for each mutant: applies it, rebuilds incrementally (about 4 s), restores the source at
  once, and runs up to `--max-runs` covering runs with `-harness-expect=<baseline>`, which
  stops at the first differing frame. Divergence, crash, early end or timeout = killed;
  otherwise survived. Mutants on lines no run executes are `no_coverage` (no build).
  Results go to `results.jsonl` (resumable); `report.md` has per-file, per-function and
  per-operator tables and a list of survivors.

## Lanes

`--lanes N` runs N workers in parallel. The coordinator records the baselines once, makes
N copies of the source tree next to the repo (`<repo>-mutlane<k>`; copies, not git
worktrees, so files stay byte-identical to the ones the mutants were enumerated from, and
the repo's version file is reused instead of asking git), builds each, and starts N
workers. Worker k takes every N-th mutant with its own build, game executable, user-files
folder, results file (`results_lane<k>.jsonl`) and restore file, and first checks that
its clean build reproduces a baseline exactly. Mutants are only ever applied in the lane
copies. With 4 lanes on this machine (8 cores, GTX 1080 Ti) one executed mutant still takes
about 19 s, so throughput is about 4x: some 1,270 mutants an hour.

Two things had to be fixed before instances could run side by side (2026-11-22):
- re3 changes system-wide Windows settings at startup and exit (foreground lock timeout,
  screen saver, power-off, sticky keys) with `SPIF_SENDCHANGE`, which broadcasts to every
  window and waits. Several instances starting or exiting at once deadlocked each other,
  and a killed instance never restored the settings. Harness runs now skip these calls.
- Opening the Windows default audio device could stall for over a minute. The tools now
  start the game with `ALSOFT_DRIVERS=null` (OpenAL's no-output backend; it must be in the
  environment at process start). The harness never needed a real device: it hashes audio
  requests and emulates playback in game time. A trace made with a real device says so in
  a `# warning` line, and is not comparable with null-audio traces.

## Running

```
# coverage profiles first (once per source change in the target files)
tools/replay_harness/coverage_build.sh
tools/replay_harness/coverage_run.sh /f/gta3 /f/gta3/harness_out/cov13 3 3000 tools/replay_harness/scenarios.txt

python tools/mutation/run.py --game-dir F:/gta3 --cov-dir F:/gta3/harness_out/cov13 \
    --files src/peds/PedFight.cpp src/peds/Ped.cpp --sample 150 --out build/mutation/run1 [--hours 3]
python tools/mutation/run.py --out build/mutation/run1 --report-only
```

The runner edits the working tree one file at a time and always restores it; if it is
killed mid-mutant, the next start restores the file from `pending.json`. Do not edit the
target files while it runs. Game windows open and close during the run; in harness mode
they no longer take focus or move the cursor.

## Scores

As in the Jellyfin and ImageMagick reports: `score = killed / (killed + survived +
no_coverage)` and `covered = killed / (killed + survived)`; timeouts and crashes count as
killed, compile errors are left out. Function verdicts use the ImageMagick gate on the
covered score: ready >= 90%, careful 75-90%, not ready < 75% (at least 5 mutants).

## Status

- Overnight sample, 2026-11-21/22: 2,100 mutants, score 36.3%, covered 64.5%
  (`results/2026-11-22/`).
- Full run, 2026-11-22: all 12,350 mutants of the same 7 files with 4 lanes, after six new
  scenarios and richer hashing: **score 39.3%, covered 65.2%** (72.8% without boundary
  operators); 37 functions ready, 67 careful, 155 not ready (`results/2026-11-22-full/`).
  Includes a correction for two baselines that drifted during the day.

Further options of `run.py`: `--lanes N`; `--only-ids FILE`; `--retest-of RESULTS`;
`--only-survivors-of RESULTS --run-offset 3`; `--hours`. At the end of every run the
coordinator re-checks all baselines against the clean build (`baseline_drift.json`).
