# Mutation testing of the replay harness, night of 2026-11-21/22

**Question:** how much of the behaviour of the likely refactoring targets does the replay
harness (`tools/replay_harness/`, 13 scenarios) actually detect?

**Operators:** the Mull profile used for ImageMagick and 3SX, `cxx_default` +
`cxx_remove_void_call`, generated at source level by `tools/mutation/mutants.py` (same
operator set as mull-runner 0.34.1, checked on a test file; counts at a given place can
differ slightly from Mull's IR-level mutants). Zero compile errors in 2,100 mutants.

**Sample:** 300 mutants per file, seeded shuffle (`--seed 1`), from 7 files with 1,190 to
2,312 mutants each (12,350 in total), so about 17% of all their mutants.

**Procedure** (`tools/mutation/run.py`):
- *Pass 1* (23:16-03:32, 4 h 15 min): each mutant on an executed line was rebuilt and run
  against up to 3 of the harness runs (scenario x seed, 3,000 frames) that execute its
  line, with `-harness-expect` stopping at the first differing frame.
- *Pass 2* (03:40-05:49): the 493 survivors were run against their covering runs 4-6.
  This killed 74 more. 65 survivors had no further covering runs, and 354 survived all six.

Raw data: `results.jsonl` (one line per mutant, merged), `report.md` (all tables,
including every function and the survivor list), `run-pass1.log`, `run-pass2.log`.

## Results

| File | Killed | Survived | No coverage | Score | Covered score |
| --- | ---: | ---: | ---: | ---: | ---: |
| `src/audio/AudioLogic.cpp` | 120 | 46 | 134 | 40.0% | 72.3% |
| `src/control/CarCtrl.cpp` | 189 | 91 | 20 | 63.0% | 67.5% |
| `src/core/Cam.cpp` | 71 | 33 | 196 | 23.7% | 68.3% |
| `src/core/Frontend.cpp` | 39 | 26 | 235 | 13.0% | 60.0% |
| `src/peds/Ped.cpp` | 143 | 87 | 70 | 47.7% | 62.2% |
| `src/peds/PedAI.cpp` | 83 | 49 | 168 | 27.7% | 62.9% |
| `src/vehicles/Automobile.cpp` | 117 | 87 | 96 | 39.0% | 57.4% |
| **all** | **762** | **419** | **919** | **36.3%** | **64.5%** |

`score = killed / (killed + survived + no coverage)`, `covered = killed / (killed +
survived)`, as in the Jellyfin and ImageMagick reports. Kills: 703 by trace divergence
(median first differing frame 767, 90th percentile 2,129), 33 crashes, 25 timeouts, 1 early
exit. Kills are concentrated in scenarios 1 and 2 only because covering runs are tried in
scenario order; that is not a ranking of the scenarios.

**By operator:** the boundary operators (`<` to `<=`, `>` to `>=` and back) are 274 of the
2,100 mutants and score 23.4% covered. Most compare floats, where hitting exactly the
boundary value practically never happens, so many are equivalent in practice. Without
them, the covered score is **71.7%** (score 39.5%). The other operators: arithmetic 61-90%,
relational negation 59-79%, `==`/`!=` swaps 47-57%, `++` to `--` 76%, void-call removal 62%.

**Functions** (ImageMagick gate on the covered score, at least 5 executed mutants): 63
functions qualify. 11 are *ready* (>= 90%), 16 *careful* (75-90%) and 36 *not ready*; the
other 363 functions had fewer than 5 executed mutants in this sample. Ready, for example:
`cAudioManager::ProcessVehicleEngine`, `ProcessBoatEngine`, `ProcessPedOneShots`,
`ProcessWeather`, `CCarCtrl::ChooseModel`, `CCarCtrl::FindPathDirection`,
`FindSplinePathPositionVector`, `CCam::WorkOutCamHeight`, `CPed::Wait`.

**More runs help somewhat:** going from 3 to 6 covering runs per survivor lifted the
covered score from 58.3% to 64.5%.

## What survives: 14 survivors read by hand

A seeded sample of non-boundary survivors from pass 1, read in the source:

| Kind | Count | Examples |
| --- | ---: | --- |
| The line runs, but the mutated part never matters in the scenarios | 6 | `this != FindPlayerVehicle()` only evaluates for an upside-down car (`CAutomobile::VehicleDamage`); `ProcessBuoyancy()` only matters for a car in water; the boat camera's collision test point; a collision-avoidance condition in `CPed::ProcessControl` |
| The effect is real but outside the trace | 4 | wheel atomics hidden in the `CAutomobile` constructor and headlight corona distance (3D rendering); `LookForSexyPeds()` (head-look and animation, not hashed); reverb channel settings |
| Equivalent in practice | 2 | a removed `RegisterReference` (matters only if the car is deleted while referenced); `++` to `--` in a loop that always stops at slot 0 |
| Data the harness does not have | 1 | savegame slot names (the user-files folder is empty) |

Line coverage overstates what the scenarios exercise: short-circuited conditions and
rare situations (flipped cars, cars in water, crowded collisions) count as covered lines.

## What this means for a refactoring campaign

- About two thirds of executed mutants are detected (72% without boundary operators). That
  is a usable but not a strong oracle: for most functions, a refactoring that only breaks
  a rare branch would pass.
- 44% of the sampled mutants sit on lines no scenario executes (`Frontend.cpp` 78%, `Cam.cpp`
  65%, `PedAI.cpp` 56%). There the harness proves nothing.
- Cheapest improvements suggested by the survivors: scenarios for the situations named
  above (cars in water, upside-down cars, night with lights, crowded pedestrian
  collisions); hashing ped head-look and animation state; longer or more seeds for the
  late-diverging cases. 3D rendering remains outside the trace.
- Function verdicts from this sample are a first cut; a function-targeted run (all mutants
  of the functions a refactoring touches) is the precise check, as `gate.py` did for
  ImageMagick.

For comparison, Jellyfin's Mull-profile score after its acceptance harness was 37.5%
(score, with no-coverage mutants counted). This run's score is 36.3%.
