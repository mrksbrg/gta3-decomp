#pragma once

// Replay harness: deterministic, input-driven runs for refactoring verification.
//
// Started with "-harness" on the command line. In harness mode the game skips the
// intro movies and the menu, starts a new game (or loads a save), advances the clock
// by a fixed 20 ms per frame, loads streamed models synchronously, drives pad 0 and
// the mouse from a seeded generator instead of real input, and writes one line of
// per-component state hashes per frame. Two builds given the same arguments must
// write identical traces; the first differing frame and column localise a
// behaviour change. See tools/replay_harness/README.md.
//
// Command line (each option is one argument):
//   -harness               enable harness mode
//   -harness-seed=N        input generator seed, and the game RNG seed (default 1)
//   -harness-frames=N      quit after N game frames (default 3000)
//   -harness-trace=PATH    trace output file (default harness_trace.csv)
//   -harness-load=N        load save slot N (1-8) instead of starting a new game
//   -harness-idle          send no input at all (useful for isolating input effects)
//   -harness-scenario=LIST start conditions, comma separated, applied at frame 30:
//                            freeroam         load data/main_freeroam.scm (no missions)
//                            armed            all hand weapons, 500 rounds each
//                            wanted=N         wanted level 1-6
//                            car=MODEL        spawn MODEL (e.g. taxi, police, rhino, dodo) and warp in
//                            boat=MODEL       find deep water nearby and start in boat MODEL (e.g. predator)
//                            at=portland|staunton|shoreside|X:Y   teleport (nearest road)
//                            hour=H           set the clock
//                            weather=sunny|cloudy|rain|fog
//                            menu             open the pause menu and navigate it with
//                                             random D-pad / Cross / back / Start presses
//   -harness-scenario-frame=N   apply the scenario at frame N instead of 30
//   -harness-userfiles=PATH user files (savegames) folder; default: a fresh empty
//                          folder harness_userfiles/p<process id> per run
//   -harness-expect=PATH   compare every frame with this baseline trace and stop at the
//                          first difference ("# diverged at frame N"); for mutation testing
//   -harness-detail        also write <trace>.detail.txt: scripts, changed script
//                          variables and vehicle fields per frame, for diagnosis

#ifdef REPLAY_HARNESS

class CHarness
{
public:
	static bool bActive;

	static bool IsActive(void) { return bActive; }

	// Returns true if arg was a harness option.
	static bool ParseArg(const char *arg);

	// Called after the INI settings are loaded: forces windowed 1280x720, no movies,
	// no frame limiter, no vsync, muted audio.
	static void ApplySettingsOverrides(void);

	// Replaces the front end. Returns true if a save game should be loaded.
	static bool PrepareStart(void);

	// Called at the start of CGame::Initialise: reseeds the game RNG.
	static void OnGameInitialise(void);

	// Elapsed real time is replaced by this many milliseconds per frame.
	static double GetFixedFrameMs(void) { return 20.0; }

	// Called in CPad::UpdatePads before pad 0 is updated: replaces all real input.
	static void InjectInput(void);

	// Called right after CStreaming::Update: finishes every pending model load now.
	static void AfterStreamingUpdate(void);

	// Called after the game logic and audio of each frame: hashes state, writes the
	// trace line, and requests quit after the last frame.
	static void EndFrame(void);

	static void Shutdown(void);

	// Harness mode keeps savegames and other user files in a fresh, empty folder per run
	// (or the one given with -harness-userfiles=PATH), never the player's own.
	static const char *GetUserFilesFolder(void);

	// Audio column: the audio code feeds every sound request of the frame in here.
	static void AddAudioRequest(const void *data, size_t size);

	// Diagnostic: appends the call stack to harness_stack.txt.
	static void ReportStack(const char *why);
};

#endif
