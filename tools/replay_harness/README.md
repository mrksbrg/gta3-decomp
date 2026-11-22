# Replay harness

Deterministic, input-driven runs of re3 for checking that a refactoring did not change
behaviour. Two builds given the same seed must write byte-identical per-frame state
traces. The first frame where they differ, and which state component differs, localises
the change.

The harness code is `src/extras/harness.{h,cpp}` plus small `#ifdef REPLAY_HARNESS` hooks.
It is compiled into Windows, D3D9, OpenAL builds with `FIX_BUGS` (see the guard at the end
of `src/core/config.h`) and does nothing unless the game is started with `-harness`.

## What harness mode changes

| Concern | What the harness does | Hook |
| --- | --- | --- |
| Start-up | Skips movies and menu, starts a new game or loads a save | `win.cpp` `GS_INIT_FRONTEND` |
| Settings | Windowed 1280x720, no frame limiter, no vsync, muted, standard controls; never written back to `re3.ini` | `Frontend.cpp` `LoadSettings`, `re3.cpp` `SaveINISettings` |
| Clock | Every frame advances exactly 20 ms of real time (timescale still applies) | `Timer.cpp` `CTimer::Update` |
| Game RNG | `myrand` reseeded with the harness seed at the start of `CGame::Initialise` | `Game.cpp` |
| Streaming | Every stream read completes before `CdStreamRead` returns, and every requested model is loaded in the frame it was requested, so load order (and so eviction) does not depend on thread timing | `CdStream_win.cpp`, `Game.cpp` after `CStreaming::Update` |
| Input | Keyboard, joystick and mouse replaced by a seeded open-loop generator (walk, sprint, mouse camera, enter/exit, fire, jump/brake, target, reverse, weapon, camera-view cycling, look left/right/behind) that never presses Start outside the `menu` scenario | `Pad.cpp` `CPad::UpdatePads` |
| Audio feedback | Whether a stream or any sample channel is still playing is decided by game time and sample length, frequency and loop count, not by the sound card | `sampman_oal.cpp` |
| Trace | One CSV line per frame after logic and audio, before rendering | `main.cpp` `Idle` |
| Audio column | Every sound request (sample, volume, pitch, position, looping, ...) the audio logic makes, hashed field by field as it enters the request queue | `AudioManager.cpp` `AddSampleToRequestedQueue` |
| Crashes | Function, line and stack written to `harness_crash.txt` and the trace | `harness.cpp` |
| 2D draw column | Every immediate-mode 2D primitive (HUD, radar, text, fades, coronas, menus): vertices and indices, via a hook pointer | `fakerw/fake.cpp` |
| User files | Savegames and other user files go to a fresh, empty `harness_userfiles\p<pid>` per run (or `-harness-userfiles=PATH`), never the player's own; settings and controller bindings are never written back to `re3.ini` | `win.cpp` `_psGetUserFilesFolder`, `re3.cpp` |
| Menu side effects | Video-mode changes from the menu are ignored (the window stays 1280x720); real mouse movement over the window is ignored; a menu Quit ends the trace with `# game quit at frame N`; "Start new game" restarts without reopening the trace | `win.cpp`, `harness.cpp` |
| Pickup glow phase | The pulse phase uses the entity's address (varies with ASLR); harness mode uses the object pool slot | `Pickups.cpp` |
| Uninitialised door target | `GoToNearestDoor` seeks an unset position when neither front door has room; harness mode zeroes it (normal play unchanged) | `PedAI.cpp` |

## Command line

```
re3.exe -harness [-harness-seed=N] [-harness-frames=N] [-harness-trace=PATH]
        [-harness-load=SLOT] [-harness-idle] [-harness-detail]
        [-harness-scenario=LIST] [-harness-scenario-frame=N]
        [-harness-jitter=MS] [-harness-stack-draw=FRAME:CALL]
```

- `-harness-seed` (default 1): seeds both the input generator and the game RNG.
- `-harness-frames` (default 3000, 60 s of game time): quit after this many frames.
- `-harness-trace` (default `harness_trace.csv`): output path.
- `-harness-load=N`: start from save slot N (1-8). Not yet verified.
- `-harness-idle`: no input at all.
- `-harness-scenario=LIST`: comma-separated start conditions, applied at frame 30
  (`-harness-scenario-frame=N` to change), after the start-up scripts have settled:
  - `freeroam`: load `data/main_freeroam.scm` (re3's mission-free script) instead of the story
  - `armed`: bat, pistol, Uzi, shotgun, AK, M16, sniper, rocket launcher, flamethrower,
    Molotovs and grenades, 500 rounds each
  - `wanted=N`: wanted level 1-6
  - `car=MODEL`: spawn MODEL (`taxi`, `police`, `rhino`, `dodo`, `firetruk`, ...) on the
    nearest road and warp in
  - `boat=MODEL`: search outward from the player for water at least 3 m deep, move there
    and start in boat MODEL (`predator`, `reefer`, ...)
  - `at=portland|staunton|shoreside|X:Y`: teleport to the nearest road, loading that level
  - `hour=H`, `weather=sunny|cloudy|rain|fog`
  - `menu`: open the pause menu and switch input to single taps of D-pad, Cross,
    Triangle, Circle and Start, so the run wanders through the menu pages (and sometimes
    resumes, restarts or quits)

  Teleports run first. Each modifier's result and the player's resulting position are
  written as `#` comment lines in the trace. `scenarios.txt` is the standard suite.
- `-harness-userfiles=PATH`: user-files folder (savegames) for the run, e.g. a copy of a
  folder with savegames for `-harness-load`. Default: a fresh empty folder per run.
- `-harness-jitter=MS`: sleep a random 0..MS ms at several points of every frame, seeded
  from the wall clock. A correct harness writes the same trace anyway; use it for the
  self-check (`compare.py --jitter 3`).
- `-harness-stack-draw=FRAME:CALL`: write the call stack of one 2D draw to
  `harness_stack.txt` (with the detail log's `D` lines, this finds who draws what).
- `-harness-detail`: also writes `<trace>.detail.txt` with, per frame, each running
  script's instruction pointer and locals, every changed script-space word, and the fields
  of every vehicle and ped (seek position, path nodes, cop state), and one `D` line per 2D
  draw. Use it to find which variable diverged.

Trace columns: `frame, time_ms, rng`, then one 64-bit FNV-1a hash per component
(`peds, vehicles, objects, player, script, camera, world, audio, draw2d`), then counts
(`n_audio` sound requests, `n_draw2d` 2D draw calls) and the player position for
orientation. `audio` covers what the audio code asks for and `draw2d` what is drawn in 2D,
not what the sound card or GPU does with it, so both are machine independent. Draws happen
while rendering, after the frame's line is written, so `draw2d` on line N is frame N-1's
drawing. The trace ends with `# end frames=N`; re3's exit code at shutdown is unreliable
(sometimes 1 after a finished run), so `compare.py` checks the marker instead. Hashes cover values only, never pointers; entities are
identified by pool slot.

## The verify gate (one command per refactoring)

```
python tools/replay_harness/verify.py --game-dir F:/gta3              # HEAD vs working tree
python tools/replay_harness/verify.py --game-dir F:/gta3 --quick      # 1 seed x 1000 frames
python tools/replay_harness/verify.py --game-dir F:/gta3 --base master~3 --seeds 3
```

It checks out and builds the baseline ref in a worktree next to the repo
(`<repo>-verify-base`, reused and built incrementally; `vendor/` is copied in once), builds
the working tree as the candidate, then runs every scenario in `scenarios.txt` for N seeds
(default 2 x 2000 frames) under 3 ms jitter. It stops at the first difference (unless
`--keep-going`), prints the scenario, seed, frame and differing columns, where the traces
are, and the `compare.py --detail` command that reruns that case with per-frame detail
logs. Exit code 0 = pass, 1 = behaviour difference, 2 = build or setup error. Prebuilt
executables can be passed with `--baseline-exe` / `--candidate-exe`. The baseline must
contain the harness.

Tested 2026-11-21 with a baseline built from a snapshot of the harness tree: unchanged
working tree PASS (8 scenarios, quick, 263 s including a 67 s full baseline build); the
`0.99f` -> `0.9901f` turn-speed mutation FAIL at new game, seed 1, frame 458, `vehicles`
(33 s, stops at the first difference).

## Comparing two builds

The game folder must be a GTA III PC install with re3's `gamefiles/` copied in, the Play
disc's `audio/` folder copied into `audio/`, and `OpenAL32.dll` and `libmpg123-0.dll`
from `vendor/*/dist/Win64/`. If the radio files were missing on an earlier run, delete
`audio/sound.cache`, which caches zero lengths.

```
python tools/replay_harness/compare.py BASE.exe CANDIDATE.exe --game-dir F:/gta3 --seeds 8 --frames 3000
python tools/replay_harness/compare.py BASE.exe CANDIDATE.exe --game-dir F:/gta3 --seeds 3 --scenario freeroam,armed,wanted=3
python tools/replay_harness/compare.py BASE.exe CANDIDATE.exe --game-dir F:/gta3 --seeds 3 --frames 2000 --jitter 3
```

Each run takes about 6 s for 3000 frames. The script copies both executables into the game
folder (re3 loads data and DLLs from there) and prints one line per seed. Exit code 0 means
every seed matched.

Build the baseline from a separate worktree so the candidate tree stays untouched:

```
git worktree add --detach ../gta3-base <base-ref>
cd ../gta3-base && git submodule update --init
./premake5.exe vs2019 --with-librw
MSBuild build/re3.sln -m -p:Configuration=Release -p:Platform=win-amd64-librw_d3d9-oal -p:PlatformToolset=v143 -p:WindowsTargetPlatformVersion=10.0
```

Both builds must contain the harness, so the baseline must be at or after the commit that
added it.

## Validation (2026-11-21)

- Self-check: one build against itself, 8 seeds x 3000 frames: 8 of 8 identical.
- Scenario self-check: the 7 scenarios in `scenarios.txt` x 3 seeds x 3000 frames:
  21 of 21 identical (after the `GoToNearestDoor` fix below).
- Mutation check: `m_vecTurnSpeed *= 0.99f` changed to `0.9901f` in
  `CPhysical::ApplyAirResistance`: 4 of 4 seeds differ, first at frames 184-458, in the
  `vehicles` column.
- Jitter self-check (all columns, random sleeps of up to 3 ms at several points per frame):
  the scenario suite x 3 seeds x 2000 frames, 21 of 21 identical. This is the strongest
  check: it showed that the earlier unjittered 21/21 results had hidden timing dependence
  (sources 4-6 below).
- Audio mutation check: the road-noise pitch factor `* 0.5f` changed to `* 0.501f` in
  `cAudioManager::ProcessVehicleRoadNoise` (`freeroam,car=taxi`, 3 seeds): all 3 differ from
  frame 2, in the `audio` column only; every other column stays identical for the whole run,
  and audio differs on 821-2532 of 3000 frames.
- Full jitter self-check, 13 scenarios x 2 seeds x 2000 frames: 26 of 26 identical.
- Menu jitter self-check: `freeroam,menu` x 4 seeds x 2000 frames under jitter: 4 of 4
  identical, including a seed that quits through the menu at frame 1048 in both runs.
- HUD mutation check: `MONEY_COLOR(89, 115, 150)` changed to `(90, 115, 150)` in `Hud.cpp`
  (`freeroam,car=taxi`, 3 seeds): all 3 differ from frame 1 in `draw2d` only.

Sources of run-to-run variation found and removed in harness mode:

1. Mission-script waits on audio used real playback: now game-time emulation (`sampman_oal.cpp`).
2. Trains and planes never initialise their steer, gas and brake fields: left out of the hash.
3. `CPed::GoToNearestDoor` passes an uninitialised `CVector` to `SetSeek` when neither front
   door has room (found with a cop chasing a player entering a car). The garbage was a heap
   pointer read as floats, so it changed with ASLR. Harness mode zeroes it. This is a real
   re3 bug and is not fixed for normal play.
4. Streamed models arrived in an order set by the streaming thread, which changed which
   models were evicted and so which peds and cars spawned: reads now complete synchronously.
5. The audio manager asked the sound card whether one-shot samples had finished: all
   channels are now emulated in game time.
6. Pickup glows pulse with a phase taken from the entity's memory address: harness mode
   uses the pool slot.

## Coverage

`coverage_build.sh` builds an LLVM source-coverage instrumented copy into `bin/coverage/`
with MSYS2's `clang-cl` (the normal build output is untouched). MSYS2's profile runtime
is built for the MinGW C runtime, so `clang_rt_msvc_shim.c` bridges the few symbols it
needs and runs its initialiser. `coverage_run.sh GAME_DIR OUT_DIR [SEEDS] [FRAMES] [SCENARIO_FILE]` runs
the harness with it and writes `report_*.txt` and `html/index.html`.

Measured 2026-11-21 (new game, re3 `src/` only, librw and vendor excluded):

| Runs | Lines | Branches | Functions |
| --- | --- | --- | --- |
| Startup only (2 idle frames) | 20.0% | 13.9% | 38.9% |
| 1 seed x 3000 frames | 34.0% | 25.3% | |
| 8 seeds x 3000 frames | 40.1% | 31.8% | 59.9% |
| `scenarios.txt`: 7 scenarios x 3 seeds x 3000 frames | 48.9% | 41.2% | |
| `scenarios.txt` with `freeroam,menu`: 8 scenarios x 3 seeds | 49.6% | 42.2% | |
| `scenarios.txt`, 13 scenarios (adds story menu, two boats, Dodo, fire truck) and camera input, x 3 seeds | 51.8% | 43.9% | |

More seeds give diminishing returns (2 seeds 34.7%, 4 seeds 38.0%); scenarios do not.
With the scenario suite, line coverage of the large files moved: `Ped.cpp` 35% to 70%,
`PedFight.cpp` 23% to 65%, `CarCtrl.cpp` 42% to 83%, `PedAI.cpp` 24% to 46%,
`Automobile.cpp` 49% to 66%, `AudioLogic.cpp` 26% to 35%, `Weapon.cpp` 5% to 33%,
`CopPed.cpp` 0% to 59%. The menu scenario lifts `Frontend.cpp` from 1.8% to 20.2% and `PCSave.cpp` from 2.5% to 19%.
Boats, the Dodo, the fire truck and camera-view input then lift `Boat.cpp` 2% to 69%,
`Heli.cpp` 6% to 44%, `WaterCannon.cpp` 21% to 89%, `Cam.cpp` 25% to 33% and `AudioLogic.cpp`
36% to 43%.
Still weak: `Cam.cpp` 33%,
mission scripts (`Script*.cpp` 17-35%), `Garages.cpp` 26%, `save/`.

## Known limits

- **Coverage.** About 49% of lines with the scenario suite (see Coverage). Missions, the
  menu, garages and saving are barely reached; save-game starts (`-harness-load`, untested)
  or menu driving would be needed.
- **Not in the trace:** 3D rendering (only 2D draws are hashed). Audio is checked as requests; the mixing, streaming and radio code
  in the sample manager and music manager is not.
- **The menu (`Frontend.cpp`, 20% covered).** The random walk reaches the pages near the
  top of the menu; deep option pages, the load/delete flows (the user-files folder is
  empty) and controller redefinition are mostly unreached.
- **One configuration.** Only the configuration you run is checked. Code compiled out of it,
  for example `#ifndef FIX_BUGS` branches, needs the build matrix and the literal guard.
- **Same machine and settings.** Traces are compared between builds on one machine with one
  `re3.ini`. Visibility checks depend on the fixed 1280x720 window.
- **Train and plane driving fields** (`m_fSteerAngle`, `m_fGasPedal`, `m_fBrakePedal`) are
  never initialised and are left out of the hash. If a refactoring starts reading them,
  the harness will not notice.
- **Uninitialised reads elsewhere.** Each one found so far was a real bug that showed up as
  a run-to-run difference. More may exist on paths the suite has not reached yet; when a
  self-check fails, use `-harness-detail` and `CHarness::ReportStack` to find the writer.
