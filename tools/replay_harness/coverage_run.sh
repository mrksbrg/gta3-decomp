#!/bin/sh
# Measures what the replay harness exercises, using the instrumented build from
# coverage_build.sh. Runs a 2-frame idle start (startup only) and, for each scenario,
# SEEDS seeds of FRAMES frames; merges the profiles and writes text reports and an HTML
# report for src/ (librw and vendor excluded).
#
# usage: tools/replay_harness/coverage_run.sh GAME_DIR OUT_DIR [SEEDS] [FRAMES] [SCENARIO_FILE]
#   SCENARIO_FILE: one -harness-scenario value per line ("newgame" = none, # = comment);
#   without it, only new-game runs are made.
#   e.g. tools/replay_harness/coverage_run.sh /f/gta3 /f/gta3/harness_out/cov 3 3000 tools/replay_harness/scenarios.txt
set -e
export ALSOFT_DRIVERS=null  # no sound device, as the other harness tools (see compare.py)
GAME=$1; OUT=$2; SEEDS=${3:-8}; FRAMES=${4:-3000}; SCENARIOS=$5
REPO=$(cd "$(dirname "$0")/../.." && pwd)
LLVM=/c/msys64/mingw64/bin
EXE="$REPO/bin/coverage/re3.exe"
mkdir -p "$OUT"
cp "$EXE" "$GAME/re3_cov.exe"
OUTW=$(cygpath -m "$OUT")

run() {
	name=$1; shift
	( cd "$GAME" && LLVM_PROFILE_FILE="$OUTW/$name.profraw" ./re3_cov.exe -harness "$@" \
		"-harness-trace=$OUTW/$name.csv" >/dev/null 2>&1 ) || true
	[ -f "$OUT/$name.profraw" ] || echo "warning: $name wrote no profile" >&2
}

run startup -harness-frames=2 -harness-idle

if [ -n "$SCENARIOS" ]; then
	grep -v '^#' "$SCENARIOS" | grep -v '^[[:space:]]*$' > "$OUT/scenarios.list"
else
	echo newgame > "$OUT/scenarios.list"
fi
k=0
while read -r sc; do
	k=$((k + 1))
	i=1
	while [ $i -le "$SEEDS" ]; do
		if [ "$sc" = newgame ]; then
			run run_s${k}_seed$i -harness-seed=$i -harness-frames=$FRAMES
		else
			run run_s${k}_seed$i -harness-seed=$i -harness-frames=$FRAMES "-harness-scenario=$sc"
		fi
		i=$((i + 1))
	done
	"$LLVM/llvm-profdata.exe" merge -sparse "$OUT"/run_s${k}_seed*.profraw -o "$OUT/scenario$k.profdata"
	echo "scenario $k ($sc): $("$LLVM/llvm-cov.exe" report "$EXE" -instr-profile="$OUT/scenario$k.profdata" \
		-ignore-filename-regex='(vendor|librw)' | grep TOTAL | awk '{print "lines " $10 ", branches " $13}')"
done < "$OUT/scenarios.list"

cd "$OUT"
"$LLVM/llvm-profdata.exe" merge -sparse startup.profraw -o startup.profdata
"$LLVM/llvm-profdata.exe" merge -sparse run_*.profraw -o all.profdata
for p in startup all; do
	"$LLVM/llvm-cov.exe" report "$EXE" -instr-profile=$p.profdata -ignore-filename-regex='(vendor|librw)' > report_$p.txt
done
"$LLVM/llvm-cov.exe" show "$EXE" -instr-profile=all.profdata -ignore-filename-regex='(vendor|librw)' \
	-format=html -show-branches=count -output-dir=html
echo "startup:  $(grep TOTAL report_startup.txt | awk '{print "lines " $10 ", branches " $13}')"
echo "all runs: $(grep TOTAL report_all.txt | awk '{print "lines " $10 ", branches " $13}')"
echo "html:     $OUT/html/index.html"
