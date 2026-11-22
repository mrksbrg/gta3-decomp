#define WITHWINDOWS
#include "common.h"

#ifdef REPLAY_HARNESS

#include "harness.h"
#include "GitSHA1.h"
#include "Pad.h"
#include "Pools.h"
#include "Ped.h"
#include "PlayerPed.h"
#include "Vehicle.h"
#include "Object.h"
#include "World.h"
#include "PlayerInfo.h"
#include "Wanted.h"
#include "Script.h"
#include "Clock.h"
#include "Weather.h"
#include "Camera.h"
#include "Timer.h"
#include "Streaming.h"
#include "Frontend.h"
#include "CutsceneMgr.h"
#include "GenericGameStorage.h"
#include "skeleton.h"
#include "WeaponInfo.h"
#include "ModelInfo.h"
#include "PathFind.h"
#include "Zones.h"
#include "Collision.h"
#include "Automobile.h"
#include "Boat.h"
#include "CopPed.h"
#include "WaterLevel.h"

#include <vector>
#include <string>

#ifdef USE_PS2_RAND
extern unsigned long long myrand_seed;
#else
extern unsigned long int myrand_seed;
#endif
extern bool gbNoMovies;

#ifdef _WIN32
#include <dbghelp.h>
#pragma comment(lib, "dbghelp.lib")
#endif

bool CHarness::bActive;

static uint32 gSeed = 1;
static int32 gMaxFrames = 3000;
static char gTracePath[260] = "harness_trace.csv";
static int32 gLoadSlot = 0; // 1-based, 0 = new game
static bool gIdle;
static bool gWantDetail;
static char gUserFilesArg[260];

// -harness-expect=PATH: a baseline trace; the run stops at the first frame that differs
// (mutation testing: a killed mutant costs only the frames up to its first effect).
static char gExpectPath[260];
static std::vector<std::string> gExpect;
static bool gExpectLoaded;

static void
LoadExpect(void)
{
	FILE *f = fopen(gExpectPath, "r");
	if(f == nil)
		return;
	char buf[512];
	bool header = true;
	while(fgets(buf, sizeof(buf), f)){
		if(buf[0] == '#')
			continue;
		if(header){ // the column line
			header = false;
			continue;
		}
		gExpect.push_back(buf);
	}
	fclose(f);
	gExpectLoaded = true;
}
static char gStartDir[260]; // working directory at start-up (the game folder)

// -harness-jitter=MS: sleep a random 0..MS milliseconds at several points per frame,
// seeded from the wall clock so every run differs. A deterministic game must still
// write the same trace; anything that does not depends on thread timing.
static int32 gJitterMaxMs;
static uint32 gJitterState;

static void
Jitter(void)
{
	if(gJitterMaxMs <= 0)
		return;
#ifdef _WIN32
	if(gJitterState == 0)
		gJitterState = (uint32)GetTickCount() ^ ((uint32)GetCurrentProcessId() << 16) | 1;
	gJitterState ^= gJitterState << 13;
	gJitterState ^= gJitterState >> 17;
	gJitterState ^= gJitterState << 5;
	Sleep(gJitterState % (uint32)(gJitterMaxMs + 1));
#endif
}

// Scenario: start conditions applied once, at gScenarioFrame (after the start-up
// scripts have settled). Modifiers are comma separated, see harness.h.
static char gScenario[256];
static int32 gScenarioFrame = 30;
static bool gFreeroam;

static FILE *gTrace;
static int32 gFrame;

// ---------------------------------------------------------------------------
// Hashing: FNV-1a 64 over values only (never pointers), so traces compare across
// builds and address-space layouts.
// ---------------------------------------------------------------------------

struct Hasher
{
	uint64 h;
	Hasher(void) : h(0xcbf29ce484222325ULL) {}
	void Bytes(const void *p, size_t n) {
		const uint8 *b = (const uint8*)p;
		for(size_t i = 0; i < n; i++){
			h ^= b[i];
			h *= 0x100000001b3ULL;
		}
	}
	void U32(uint32 v) { Bytes(&v, sizeof(v)); }
	void I32(int32 v) { Bytes(&v, sizeof(v)); }
	void U64(uint64 v) { Bytes(&v, sizeof(v)); }
	void F(float v) { Bytes(&v, sizeof(v)); }
	void Vec(const CVector &v) { F(v.x); F(v.y); F(v.z); }
	void Mat(const CMatrix &m) { Vec(m.GetRight()); Vec(m.GetForward()); Vec(m.GetUp()); Vec(m.GetPosition()); }
};

static void
HashPhysical(Hasher &hs, CPhysical *e)
{
	hs.I32(e->GetModelIndex());
	hs.U32(e->GetStatus());
	hs.Mat(e->GetMatrix());
	hs.Vec(e->GetMoveSpeed());
	hs.Vec(e->GetTurnSpeed());
}

// An entity reference as a value: pool kind and slot, never the pointer.
static int32
EntityRef(CEntity *e)
{
	if(e == nil)
		return -1;
	if(e->IsPed())
		return 0x10000 + CPools::GetPedPool()->GetJustIndex_NoFreeAssert((CPed*)e);
	if(e->IsVehicle())
		return 0x20000 + CPools::GetVehiclePool()->GetJustIndex_NoFreeAssert((CVehicle*)e);
	if(e->IsObject())
		return 0x30000 + CPools::GetObjectPool()->GetJustIndex_NoFreeAssert((CObject*)e);
	return 0x40000 + e->GetModelIndex(); // buildings and dummies: their model
}

static uint64
HashPeds(int32 &count)
{
	Hasher hs;
	count = 0;
	CPedPool *pool = CPools::GetPedPool();
	for(int32 i = 0; i < pool->GetSize(); i++){
		CPed *ped = pool->GetSlot(i);
		if(ped == nil)
			continue;
		count++;
		hs.I32(i);
		HashPhysical(hs, ped);
		hs.F(ped->m_fHealth);
		hs.F(ped->m_fArmour);
		hs.I32(ped->m_nPedState);
		hs.I32(ped->m_objective);
		hs.U32(ped->bInVehicle);
		hs.I32(ped->m_pMyVehicle ? CPools::GetVehiclePool()->GetIndex(ped->m_pMyVehicle) : -1);
		// steering and seeking state, which mutation testing showed changes before the
		// ped's position does (2026-11-22)
		hs.F(ped->m_fRotationCur);
		hs.F(ped->m_fRotationDest);
		hs.I32(ped->m_nMoveState);
		hs.Vec(ped->m_vecSeekPos);
		hs.I32(EntityRef(ped->m_pSeekTarget));
		hs.I32(EntityRef(ped->m_pLookTarget));
		hs.F(ped->m_fLookDirection);
		hs.U32(ped->bIsLooking);
	}
	return hs.h;
}

static uint64
HashVehicles(int32 &count)
{
	Hasher hs;
	count = 0;
	CVehiclePool *pool = CPools::GetVehiclePool();
	for(int32 i = 0; i < pool->GetSize(); i++){
		CVehicle *veh = pool->GetSlot(i);
		if(veh == nil)
			continue;
		count++;
		hs.I32(i);
		HashPhysical(hs, veh);
		hs.F(veh->m_fHealth);
		hs.U32(veh->m_nCurrentGear);
		// Trains and planes never initialise or read the driving controls; hashing
		// them would hash leftover heap memory.
		if(veh->IsCar() || veh->IsBoat()){
			hs.F(veh->m_fSteerAngle);
			hs.F(veh->m_fGasPedal);
			hs.F(veh->m_fBrakePedal);
			// the traffic AI's plan, which changes before the car's path does (2026-11-22)
			const CAutoPilot &ap = veh->AutoPilot;
			hs.I32(ap.m_nCurrentRouteNode);
			hs.I32(ap.m_nNextRouteNode);
			hs.I32(ap.m_nPrevRouteNode);
			hs.I32(ap.m_nCurrentLane);
			hs.I32(ap.m_nNextLane);
			hs.U32(ap.m_nDrivingStyle);
			hs.U32(ap.m_nCarMission);
			hs.U32(ap.m_nCruiseSpeed);
			hs.F(ap.m_fMaxTrafficSpeed);
		}
		if(veh->IsCar()){
			// wheels, suspension and doors: state the body position does not show
			CAutomobile *car = (CAutomobile*)veh;
			for(int32 w = 0; w < 4; w++){
				hs.F(car->m_aSuspensionSpringRatio[w]);
				hs.F(car->m_aWheelRotation[w]);
				hs.F(car->m_aWheelSpeed[w]);
			}
			for(int32 d = 0; d < 6; d++)
				hs.F(car->Doors[d].m_fAngle);
		}
	}
	return hs.h;
}

static uint64
HashObjects(int32 &count)
{
	Hasher hs;
	count = 0;
	CObjectPool *pool = CPools::GetObjectPool();
	for(int32 i = 0; i < pool->GetSize(); i++){
		CObject *obj = pool->GetSlot(i);
		if(obj == nil)
			continue;
		count++;
		hs.I32(i);
		HashPhysical(hs, obj);
	}
	return hs.h;
}

static uint64
HashPlayer(void)
{
	Hasher hs;
	CPlayerInfo &info = CWorld::Players[CWorld::PlayerInFocus];
	hs.I32(info.m_nMoney);
	CPlayerPed *player = FindPlayerPed();
	if(player){
		hs.Mat(player->GetMatrix());
		hs.F(player->m_fHealth);
		hs.F(player->m_fArmour);
		if(player->m_pWanted){
			hs.I32(player->m_pWanted->m_nWantedLevel);
			hs.I32(player->m_pWanted->m_nChaos);
		}
	}
	return hs.h;
}

static uint64
HashScript(void)
{
	Hasher hs;
	hs.Bytes(CTheScripts::ScriptSpace, sizeof(CTheScripts::ScriptSpace));
	for(CRunningScript *s = CTheScripts::pActiveScripts; s; s = s->next){
		hs.Bytes(s->m_abScriptName, sizeof(s->m_abScriptName));
		hs.U32(s->m_nIp);
		hs.U32(s->m_nStackPointer);
		hs.Bytes(s->m_anStack, sizeof(s->m_anStack));
		hs.Bytes(s->m_anLocalVariables, sizeof(s->m_anLocalVariables));
		hs.U32(s->m_nWakeTime);
		hs.U32(s->m_bCondResult);
	}
	return hs.h;
}

// -harness-detail: per frame, each running script and every changed 4-byte word of
// script space, so a script-only divergence can be traced to a variable.
static FILE *gDetail;
static uint8 *gPrevScriptSpace;

static void
WriteScriptDetail(void)
{
	if(gDetail == nil)
		return;
	for(CRunningScript *s = CTheScripts::pActiveScripts; s; s = s->next){
		Hasher locals;
		locals.Bytes(s->m_anLocalVariables, sizeof(s->m_anLocalVariables));
		fprintf(gDetail, "%d S %.8s ip=%u wake=%u sp=%u cond=%d locals=%016llx\n", gFrame, s->m_abScriptName,
			s->m_nIp, s->m_nWakeTime, (uint32)s->m_nStackPointer, s->m_bCondResult ? 1 : 0, (unsigned long long)locals.h);
	}
	fprintf(gDetail, "%d M active=%d screen=%d option=%d prev=%d showmouse=%d\n", gFrame,
		FrontEndMenuManager.m_bMenuActive ? 1 : 0, FrontEndMenuManager.m_nCurrScreen, FrontEndMenuManager.m_nCurrOption,
		FrontEndMenuManager.m_nPrevScreen, FrontEndMenuManager.m_bShowMouse ? 1 : 0);
	CVehiclePool *vehPool = CPools::GetVehiclePool();
	for(int32 i = 0; i < vehPool->GetSize(); i++){
		CVehicle *veh = vehPool->GetSlot(i);
		if(veh == nil)
			continue;
		Hasher mat;
		mat.Mat(veh->GetMatrix());
		const CVector &pos = veh->GetPosition();
		const CVector &ms = veh->GetMoveSpeed();
		const CVector &ts = veh->GetTurnSpeed();
		fprintf(gDetail, "%d V %d model=%d status=%u pos=%a,%a,%a mat=%016llx move=%a,%a,%a turn=%a,%a,%a health=%a gear=%u steer=%a gas=%a brake=%a\n",
			gFrame, i, veh->GetModelIndex(), (uint32)veh->GetStatus(), pos.x, pos.y, pos.z, (unsigned long long)mat.h,
			ms.x, ms.y, ms.z, ts.x, ts.y, ts.z, veh->m_fHealth, (uint32)veh->m_nCurrentGear,
			veh->m_fSteerAngle, veh->m_fGasPedal, veh->m_fBrakePedal);
	}
	CPedPool *pedPool = CPools::GetPedPool();
	for(int32 i = 0; i < pedPool->GetSize(); i++){
		CPed *ped = pedPool->GetSlot(i);
		if(ped == nil)
			continue;
		Hasher mat;
		mat.Mat(ped->GetMatrix());
		const CVector &pos = ped->GetPosition();
		const CVector &ms = ped->GetMoveSpeed();
		fprintf(gDetail, "%d P %d model=%d type=%d state=%d obj=%d pos=%a,%a,%a mat=%016llx move=%a,%a,%a health=%a armour=%a weapon=%d invehicle=%d\n",
			gFrame, i, ped->GetModelIndex(), (int)ped->m_nPedType, (int)ped->m_nPedState, (int)ped->m_objective,
			pos.x, pos.y, pos.z, (unsigned long long)mat.h, ms.x, ms.y, ms.z, ped->m_fHealth, ped->m_fArmour,
			(int)ped->GetWeapon()->m_eWeaponType, ped->bInVehicle ? 1 : 0);
		fprintf(gDetail, "%d P+ %d seek=%a,%a,%a offseek=%a,%a,%a rot=%a->%a move=%d timer=%u pathnode=%d dir=%d seekdone=%a\n",
			gFrame, i, ped->m_vecSeekPos.x, ped->m_vecSeekPos.y, ped->m_vecSeekPos.z,
			ped->m_vecOffsetSeek.x, ped->m_vecOffsetSeek.y, ped->m_vecOffsetSeek.z,
			ped->m_fRotationCur, ped->m_fRotationDest, (int)ped->m_nMoveState, ped->m_nPedStateTimer,
			(int)ped->m_nCurPathNode, (int)ped->m_nPathDir, ped->m_distanceToCountSeekDone);
		// path node pointers as indices into ThePaths.m_pathNodes (out of range = not a node)
		fprintf(gDetail, "%d PN %d next=%lld last=%lld\n", gFrame, i,
			ped->m_pNextPathNode ? (long long)(ped->m_pNextPathNode - ThePaths.m_pathNodes) : -999999LL,
			ped->m_pLastPathNode ? (long long)(ped->m_pLastPathNode - ThePaths.m_pathNodes) : -999999LL);
		if(ped->m_nPedType == PEDTYPE_COP){
			CCopPed *cop = (CCopPed*)ped;
			fprintf(gDetail, "%d C %d dist=%a pursuit=%d roadblock=%d beating=%d type=%d\n", gFrame, i,
				cop->m_fDistanceToTarget, cop->m_bIsInPursuit ? 1 : 0, (int)cop->m_nRoadblockNode,
				cop->m_bBeatingSuspect ? 1 : 0, (int)cop->m_nCopType);
		}
	}
	if(gPrevScriptSpace == nil){
		gPrevScriptSpace = new uint8[sizeof(CTheScripts::ScriptSpace)];
		memcpy(gPrevScriptSpace, CTheScripts::ScriptSpace, sizeof(CTheScripts::ScriptSpace));
		return;
	}
	for(uint32 off = 0; off + 4 <= sizeof(CTheScripts::ScriptSpace); off += 4){
		int32 now, before;
		memcpy(&now, &CTheScripts::ScriptSpace[off], 4);
		memcpy(&before, &gPrevScriptSpace[off], 4);
		if(now != before)
			fprintf(gDetail, "%d G %u %d -> %d\n", gFrame, off, before, now);
	}
	memcpy(gPrevScriptSpace, CTheScripts::ScriptSpace, sizeof(CTheScripts::ScriptSpace));
}

// Audio: every sound request the audio code makes in a frame, in order.
static Hasher gAudioHash;

// 2D draws (HUD, radar, text, fades, menus): every immediate-mode 2D primitive, via the
// gHarnessDraw2DHook in src/fakerw/fake.cpp. Draws happen while rendering, after the
// frame's trace line, so each line carries the previous frame's draws.
static Hasher gDrawHash;
static int32 gDrawCalls;
static int32 gStackDrawFrame = -1, gStackDrawCall = -1; // -harness-stack-draw=FRAME:CALL

#ifdef LIBRW
extern void (*gHarnessDraw2DHook)(int primType, const void *vertices, int numVertices, int vertexSize, const void *indices, int numIndices);

static void
HarnessDraw2D(int primType, const void *vertices, int numVertices, int vertexSize, const void *indices, int numIndices)
{
	Hasher one;
	one.I32(primType);
	one.I32(numVertices);
	one.Bytes(vertices, (size_t)numVertices * vertexSize);
	one.I32(numIndices);
	if(indices && numIndices > 0)
		one.Bytes(indices, (size_t)numIndices * sizeof(uint16));
	gDrawHash.U64(one.h);
	if(gDetail){
		// first vertex position and colour make the draw recognisable on screen
		const float *v = (const float*)vertices;
		fprintf(gDetail, "%d D %d prim=%d verts=%d idx=%d hash=%016llx v0=%.1f,%.1f col=%08x\n", gFrame, gDrawCalls,
			primType, numVertices, numIndices, (unsigned long long)one.h,
			numVertices > 0 ? v[0] : 0.0f, numVertices > 0 ? v[1] : 0.0f, numVertices > 0 ? ((const uint32*)vertices)[4] : 0u);
	}
	if(gFrame == gStackDrawFrame && gDrawCalls == gStackDrawCall)
		CHarness::ReportStack("draw2d call requested by -harness-stack-draw");
	gDrawCalls++;
}
#endif
static int32 gAudioRequests;

void
CHarness::AddAudioRequest(const void *data, size_t size)
{
	gAudioHash.Bytes(data, size);
	gAudioRequests++;
}

static uint64
HashCamera(void)
{
	Hasher hs;
	hs.Mat(TheCamera.GetMatrix());
	// the active camera's own state: mode, angles, field of view (2026-11-22)
	const CCam &cam = TheCamera.Cams[TheCamera.ActiveCam];
	hs.U32(TheCamera.ActiveCam);
	hs.I32(cam.Mode);
	hs.F(cam.FOV);
	hs.F(cam.Alpha);
	hs.F(cam.Beta);
	hs.Vec(cam.Source);
	hs.Vec(cam.Front);
	return hs.h;
}

static uint64
HashWorld(void)
{
	Hasher hs;
	hs.U32(CClock::ms_nGameClockHours);
	hs.U32(CClock::ms_nGameClockMinutes);
	hs.U32(CClock::ms_nGameClockSeconds);
	hs.I32(CWeather::OldWeatherType);
	hs.I32(CWeather::NewWeatherType);
	hs.F(CWeather::InterpolationValue);
	hs.F(CWeather::Wind);
	hs.U32(CCutsceneMgr::IsRunning());
	hs.U32(FrontEndMenuManager.m_bMenuActive);
	return hs.h;
}

// ---------------------------------------------------------------------------
// Input generator: open loop (never reads game state), seeded, xorshift64*.
// ---------------------------------------------------------------------------

enum eAction
{
	ACT_IDLE,
	ACT_MOVE,
	ACT_SPRINT,
	ACT_CAMERA,
	ACT_ENTER_EXIT,
	ACT_FIRE,
	ACT_JUMP_BRAKE,
	ACT_TARGET,
	ACT_REVERSE,
	ACT_WEAPON,
	ACT_CAMERA_MODE,	// Select: cycle camera views (on foot and in vehicles)
	ACT_LOOK,		// shoulder 2 buttons (look left/right/behind in a car), L3 (behind on foot)
	NUM_ACTIONS
};

static const int32 aActionWeights[NUM_ACTIONS] = { 1, 4, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1 };

static struct
{
	uint64 s;
	int32 action;
	int32 remaining;
	int32 age;
	int16 stickX, stickY;
	float mouseX, mouseY;
} gGen;

static uint32
GenNext(void)
{
	gGen.s ^= gGen.s >> 12;
	gGen.s ^= gGen.s << 25;
	gGen.s ^= gGen.s >> 27;
	return (uint32)((gGen.s * 0x2545F4914F6CDD1DULL) >> 32);
}

static int32
GenRange(int32 lo, int32 hi)
{
	return lo + (int32)(GenNext() % (uint32)(hi - lo + 1));
}

static void
GenNewSegment(void)
{
	int32 total = 0;
	for(int32 i = 0; i < NUM_ACTIONS; i++)
		total += aActionWeights[i];
	int32 r = GenRange(0, total - 1);
	gGen.action = 0;
	while(r >= aActionWeights[gGen.action]){
		r -= aActionWeights[gGen.action];
		gGen.action++;
	}
	gGen.remaining = GenRange(10, 120);
	gGen.age = 0;
	gGen.stickX = (int16)GenRange(-128, 128);
	gGen.stickY = (int16)GenRange(-128, 0);
	gGen.mouseX = (float)GenRange(-15, 15);
	gGen.mouseY = (float)GenRange(-3, 3);
}

// Menu mode ("menu" scenario modifier): single taps of the buttons the menu reads,
// each followed by a few idle frames so it sees a press and a release.
static bool gMenuMode;

enum eHarnessMenuAction
{
	MACT_IDLE, MACT_UP, MACT_DOWN, MACT_LEFT, MACT_RIGHT, MACT_SELECT, MACT_BACK, MACT_BACK2, MACT_START,
	NUM_MENU_ACTIONS
};
static const int32 aMenuActionWeights[NUM_MENU_ACTIONS] = { 2, 3, 3, 2, 2, 3, 2, 1, 1 };

static void
GenMenuFrame(CControllerState &pad)
{
	if(gGen.remaining <= 0){
		int32 total = 0;
		for(int32 i = 0; i < NUM_MENU_ACTIONS; i++)
			total += aMenuActionWeights[i];
		int32 r = GenRange(0, total - 1);
		gGen.action = 0;
		while(r >= aMenuActionWeights[gGen.action]){
			r -= aMenuActionWeights[gGen.action];
			gGen.action++;
		}
		gGen.remaining = GenRange(3, 20);
		gGen.age = 0;
	}
	gGen.remaining--;
	bool tap = gGen.age < 1;
	gGen.age++;
	if(!tap)
		return;
	switch(gGen.action){
	case MACT_UP: pad.DPadUp = 255; break;
	case MACT_DOWN: pad.DPadDown = 255; break;
	case MACT_LEFT: pad.DPadLeft = 255; break;
	case MACT_RIGHT: pad.DPadRight = 255; break;
	case MACT_SELECT: pad.Cross = 255; break;
	case MACT_BACK: pad.Triangle = 255; break;
	case MACT_BACK2: pad.Circle = 255; break;
	case MACT_START: pad.Start = 255; break;
	}
}

static void
GenFrame(CControllerState &pad, CMouseControllerState &mouse)
{
	pad.Clear();
	mouse.Clear();
	if(gIdle)
		return;
	if(gMenuMode){
		GenMenuFrame(pad);
		return;
	}

	if(gGen.remaining <= 0)
		GenNewSegment();
	gGen.remaining--;
	bool tap = gGen.age < 2;
	gGen.age++;

	switch(gGen.action){
	case ACT_IDLE:
		break;
	case ACT_MOVE:
		pad.LeftStickX = gGen.stickX;
		pad.LeftStickY = gGen.stickY;
		break;
	case ACT_SPRINT:
		pad.LeftStickX = gGen.stickX / 4;
		pad.LeftStickY = -128;
		pad.Cross = 255;
		break;
	case ACT_CAMERA:
		mouse.x = gGen.mouseX;
		mouse.y = gGen.mouseY;
		break;
	case ACT_ENTER_EXIT:
		if(tap)
			pad.Triangle = 255;
		break;
	case ACT_FIRE:
		pad.LeftStickX = gGen.stickX / 2;
		pad.Circle = 255;
		mouse.LMB = true;
		break;
	case ACT_JUMP_BRAKE:
		pad.LeftStickY = gGen.stickY;
		pad.Square = tap ? 255 : 0;
		break;
	case ACT_TARGET:
		pad.RightShoulder1 = 255;
		pad.Circle = (gGen.age & 8) ? 255 : 0;
		break;
	case ACT_REVERSE:
		pad.LeftStickX = gGen.stickX;
		pad.LeftStickY = 128;
		pad.Square = 255;
		break;
	case ACT_WEAPON:
		if(tap)
			mouse.WHEELUP = true;
		break;
	case ACT_CAMERA_MODE:
		pad.LeftStickX = gGen.stickX;
		pad.LeftStickY = gGen.stickY;
		if(tap)
			pad.Select = 255;
		break;
	case ACT_LOOK:
		// the stick value picks the variant, so it stays fixed for the whole segment
		pad.LeftStickY = gGen.stickY;
		if(gGen.stickX < -64)
			pad.LeftShoulder2 = 255;
		else if(gGen.stickX < 0)
			pad.RightShoulder2 = 255;
		else if(gGen.stickX < 64){
			pad.LeftShoulder2 = 255;
			pad.RightShoulder2 = 255;
		}else
			pad.LeftShock = 255;
		break;
	}
}

// ---------------------------------------------------------------------------
// Scenarios: built from the same calls the debug menu (re3.cpp) and the
// WARP_PLAYER_INTO_CAR / GIVE_WEAPON_TO_PLAYER script commands use.
// ---------------------------------------------------------------------------

static bool
ScenarioTeleport(CVector target)
{
	// snap to the nearest car path node so the player lands on a road
	int32 node = ThePaths.FindNodeClosestToCoors(target, 0, 400.0f, false, false);
	if(node >= 0)
		target = ThePaths.m_pathNodes[node].GetPosition();
	CEntity *ent = FindPlayerEntity();
	if(ent == nil)
		return false;
	CGame::currLevel = CTheZones::GetLevelFromPosition(&target);
	CCollision::SortOutCollisionAfterLoad();
	CStreaming::LoadScene(target);
	target.z = CWorld::FindGroundZForCoord(target.x, target.y) + ent->GetDistanceFromCentreOfMassToBaseOfModel();
	ent->Teleport(target);
	CStreaming::LoadScene(target);
	return true;
}

static bool
ScenarioCar(const char *name)
{
	int id;
	if(CModelInfo::GetModelInfo(name, &id) == nil)
		return false;
	CStreaming::RequestModel(id, STREAMFLAGS_DONT_REMOVE);
	CStreaming::LoadAllRequestedModels(false);
	if(!CStreaming::HasModelLoaded(id))
		return false;
	CPlayerPed *player = FindPlayerPed();
	if(player == nil || player->bInVehicle)
		return false;
	CVector pos = player->GetPosition();
	CVehicle *v;
	if(CModelInfo::IsBoatModel(id)){
		v = new CBoat(id, MISSION_VEHICLE);
	}else{
		int32 node = ThePaths.FindNodeClosestToCoors(pos, 0, 100.0f, false, false);
		if(node >= 0)
			pos = ThePaths.m_pathNodes[node].GetPosition();
		v = new CAutomobile(id, MISSION_VEHICLE);
	}
	v->SetPosition(pos + CVector(0.0f, 0.0f, 2.0f));
	v->SetOrientation(0.0f, 0.0f, 0.0f);
	v->SetStatus(STATUS_ABANDONED);
	v->m_nDoorLock = CARLOCK_UNLOCKED;
	v->bHasBeenOwnedByPlayer = true;
	CWorld::Add(v);
	player->SetObjective(OBJECTIVE_ENTER_CAR_AS_DRIVER, v);
	player->WarpPedIntoCar(v);
	return true;
}

// Rings around origin, out to 400 m: the first spot where the sea is at least 3 m deep.
static bool
FindDeepWater(const CVector &origin, CVector &spot)
{
	float level = 0.0f;
	for(float r = 10.0f; r <= 400.0f; r += 10.0f)
		for(int32 a = 0; a < 32; a++){
			float angle = a * (TWOPI / 32.0f);
			CVector p = origin + CVector(r * Cos(angle), r * Sin(angle), 0.0f);
			if(CWaterLevel::GetWaterLevelNoWaves(p.x, p.y, p.z, &level) &&
			   CWorld::FindGroundZForCoord(p.x, p.y) < level - 3.0f){
				spot = CVector(p.x, p.y, level);
				return true;
			}
		}
	return false;
}

// Puts the player's car into deep water nearby (buoyancy, sinking, getting out).
static bool
ScenarioInWater(void)
{
	CVehicle *veh = FindPlayerVehicle();
	CVector spot;
	if(veh == nil || !FindDeepWater(veh->GetPosition(), spot))
		return false;
	CStreaming::LoadScene(spot);
	veh->Teleport(spot + CVector(0.0f, 0.0f, 1.0f));
	return true;
}

// Turns the player's car upside down where it stands (flipped-car damage and recovery).
static bool
ScenarioFlip(void)
{
	CVehicle *veh = FindPlayerVehicle();
	if(veh == nil)
		return false;
	CVector pos = veh->GetPosition() + CVector(0.0f, 0.0f, 1.5f);
	veh->SetOrientation(0.0f, PI, 0.0f); // rolled 180 degrees about the forward axis
	veh->SetPosition(pos);
	veh->SetMoveSpeed(0.0f, 0.0f, 0.0f);
	veh->SetTurnSpeed(0.0f, 0.0f, 0.0f);
	return true;
}

// Selects a weapon the player owns, as the SET_CURRENT_PLAYER_WEAPON script command does.
static bool
ScenarioWeapon(const char *name)
{
	static const struct { const char *name; eWeaponType type; } names[] = {
		{ "bat", WEAPONTYPE_BASEBALLBAT }, { "pistol", WEAPONTYPE_COLT45 }, { "uzi", WEAPONTYPE_UZI },
		{ "shotgun", WEAPONTYPE_SHOTGUN }, { "ak47", WEAPONTYPE_AK47 }, { "m16", WEAPONTYPE_M16 },
		{ "sniper", WEAPONTYPE_SNIPERRIFLE }, { "rocket", WEAPONTYPE_ROCKETLAUNCHER },
		{ "flame", WEAPONTYPE_FLAMETHROWER }, { "molotov", WEAPONTYPE_MOLOTOV }, { "grenade", WEAPONTYPE_GRENADE }
	};
	CPlayerPed *player = FindPlayerPed();
	if(player == nil)
		return false;
	for(int32 n = 0; n < ARRAY_SIZE(names); n++){
		if(strcmp(name, names[n].name) != 0)
			continue;
		for(int32 i = 0; i < WEAPONTYPE_TOTAL_INVENTORY_WEAPONS; i++)
			if(player->m_weapons[i].m_eWeaponType == names[n].type){
				player->m_nSelectedWepSlot = i;
				return true;
			}
		return false; // not owned: put "armed" first
	}
	return false;
}

// Boats need water: move the player to deep water nearby and start them in the boat.
static bool
ScenarioBoat(const char *name)
{
	int id;
	if(CModelInfo::GetModelInfo(name, &id) == nil || !CModelInfo::IsBoatModel(id))
		return false;
	CPlayerPed *player = FindPlayerPed();
	if(player == nil || player->bInVehicle)
		return false;
	CVector spot;
	if(!FindDeepWater(player->GetPosition(), spot))
		return false;
	CStreaming::RequestModel(id, STREAMFLAGS_DONT_REMOVE);
	CStreaming::LoadAllRequestedModels(false);
	if(!CStreaming::HasModelLoaded(id))
		return false;
	player->Teleport(spot + CVector(0.0f, 0.0f, 2.0f));
	CStreaming::LoadScene(spot);
	CVehicle *v = new CBoat(id, MISSION_VEHICLE);
	v->SetPosition(spot + CVector(0.0f, 0.0f, 1.0f));
	v->SetOrientation(0.0f, 0.0f, 0.0f);
	v->SetStatus(STATUS_ABANDONED);
	v->m_nDoorLock = CARLOCK_UNLOCKED;
	v->bHasBeenOwnedByPlayer = true;
	CWorld::Add(v);
	player->SetObjective(OBJECTIVE_ENTER_CAR_AS_DRIVER, v);
	player->WarpPedIntoCar(v);
	return true;
}

static void
ScenarioArm(void)
{
	static const eWeaponType weapons[] = {
		WEAPONTYPE_BASEBALLBAT, WEAPONTYPE_COLT45, WEAPONTYPE_UZI, WEAPONTYPE_SHOTGUN,
		WEAPONTYPE_AK47, WEAPONTYPE_M16, WEAPONTYPE_SNIPERRIFLE, WEAPONTYPE_ROCKETLAUNCHER,
		WEAPONTYPE_FLAMETHROWER, WEAPONTYPE_MOLOTOV, WEAPONTYPE_GRENADE
	};
	CPlayerPed *player = FindPlayerPed();
	if(player == nil)
		return;
	for(int32 i = 0; i < ARRAY_SIZE(weapons); i++){
		int32 model = CWeaponInfo::GetWeaponInfo(weapons[i])->m_nModelId;
		if(model >= 0)
			CStreaming::RequestModel(model, STREAMFLAGS_DONT_REMOVE);
	}
	CStreaming::LoadAllRequestedModels(false);
	for(int32 i = 0; i < ARRAY_SIZE(weapons); i++)
		player->m_nSelectedWepSlot = player->GiveWeapon(weapons[i], 500);
}

static bool
ApplyModifier(const char *tok)
{
	if(strcmp(tok, "freeroam") == 0)
		return true; // applied at CGame::Initialise
	if(strcmp(tok, "menu") == 0){
		gMenuMode = true;
		FrontEndMenuManager.RequestFrontEndStartUp();
		return true;
	}
	if(strcmp(tok, "armed") == 0){
		ScenarioArm();
		return FindPlayerPed() != nil;
	}
	if(strncmp(tok, "weapon=", 7) == 0)
		return ScenarioWeapon(tok + 7);
	if(strcmp(tok, "inwater") == 0)
		return ScenarioInWater();
	if(strcmp(tok, "flip") == 0)
		return ScenarioFlip();
	if(strcmp(tok, "controls=classic") == 0){
		// classic (pad-style) controls: the camera follows without the mouse
		CMenuManager::m_ControlMethod = CONTROL_CLASSIC;
		TheCamera.m_bUseMouse3rdPerson = false;
		return true;
	}
#ifdef FREE_CAM
	if(strcmp(tok, "freecam") == 0){
		// re3's rotatable camera (the San Andreas style follow cameras)
		TheCamera.bFreeCam = true;
		return true;
	}
#endif
	if(strncmp(tok, "wanted=", 7) == 0){
		if(FindPlayerPed() == nil)
			return false;
		FindPlayerPed()->SetWantedLevel(atoi(tok + 7));
		return true;
	}
	if(strncmp(tok, "car=", 4) == 0)
		return ScenarioCar(tok + 4);
	if(strncmp(tok, "boat=", 5) == 0)
		return ScenarioBoat(tok + 5);
	if(strncmp(tok, "hour=", 5) == 0){
		CClock::SetGameClock(atoi(tok + 5), 0);
		return true;
	}
	if(strncmp(tok, "weather=", 8) == 0){
		const char *w = tok + 8;
		int16 type = strcmp(w, "sunny") == 0 ? WEATHER_SUNNY : strcmp(w, "cloudy") == 0 ? WEATHER_CLOUDY :
			strcmp(w, "rain") == 0 ? WEATHER_RAINY : strcmp(w, "fog") == 0 ? WEATHER_FOGGY : -1;
		if(type < 0)
			return false;
		CWeather::ForceWeatherNow(type);
		return true;
	}
	if(strcmp(tok, "at=portland") == 0)
		return ScenarioTeleport(CVector(905.0f, -686.0f, 20.0f));
	if(strcmp(tok, "at=staunton") == 0)
		return ScenarioTeleport(CVector(400.0f, -700.0f, 20.0f));
	if(strcmp(tok, "at=shoreside") == 0)
		return ScenarioTeleport(CVector(-1110.0f, -88.0f, 20.0f));
	if(strncmp(tok, "at=", 3) == 0){
		float x, y;
		return sscanf(tok + 3, "%f:%f", &x, &y) == 2 && ScenarioTeleport(CVector(x, y, 20.0f));
	}
	return false;
}

static void
ApplyScenario(void)
{
	// teleport first, so the car is spawned and the weapons given at the destination
	char buf[256];
	strcpy(buf, gScenario);
	char *toks[16];
	int32 n = 0;
	for(char *tok = strtok(buf, ","); tok && n < 16; tok = strtok(nil, ","))
		toks[n++] = tok;
	for(int32 pass = 0; pass < 2; pass++)
		for(int32 i = 0; i < n; i++){
			bool isTeleport = strncmp(toks[i], "at=", 3) == 0;
			if(isTeleport != (pass == 0))
				continue;
			bool ok = ApplyModifier(toks[i]);
			if(gTrace)
				fprintf(gTrace, "# scenario frame %d: %s %s\n", gFrame, toks[i], ok ? "ok" : "FAILED");
		}
	if(gTrace){
		CVector pos = FindPlayerCoors();
		fprintf(gTrace, "# scenario frame %d: player at %.1f,%.1f,%.1f level %d in vehicle %d\n", gFrame,
			pos.x, pos.y, pos.z, (int)CGame::currLevel, FindPlayerVehicle() ? 1 : 0);
	}
}

// ---------------------------------------------------------------------------
// Crash report: an unattended run that crashes should say where, in
// harness_crash.txt (working directory) and at the end of the trace.
// ---------------------------------------------------------------------------

#ifdef _WIN32
static void
WriteStack(FILE *f)
{
	static bool symInit;
	HANDLE proc = GetCurrentProcess();
	if(!symInit){
		SymSetOptions(SYMOPT_LOAD_LINES | SYMOPT_UNDNAME);
		SymInitialize(proc, nil, TRUE);
		symInit = true;
	}
	void *frames[48];
	USHORT n = CaptureStackBackTrace(0, 48, frames, nil);
	char symBuf[sizeof(SYMBOL_INFO) + 256];
	SYMBOL_INFO *sym = (SYMBOL_INFO*)symBuf;
	for(USHORT i = 0; i < n; i++){
		DWORD64 addr = (DWORD64)frames[i];
		memset(symBuf, 0, sizeof(symBuf));
		sym->SizeOfStruct = sizeof(SYMBOL_INFO);
		sym->MaxNameLen = 255;
		DWORD64 disp = 0;
		DWORD lineDisp = 0;
		IMAGEHLP_LINE64 line;
		memset(&line, 0, sizeof(line));
		line.SizeOfStruct = sizeof(line);
		const char *name = SymFromAddr(proc, addr, &disp, sym) ? sym->Name : "?";
		if(SymGetLineFromAddr64(proc, addr, &lineDisp, &line))
			fprintf(f, "#   %s  %s:%lu\n", name, line.FileName, (unsigned long)line.LineNumber);
		else
			fprintf(f, "#   %s  0x%llx\n", name, (unsigned long long)addr);
	}
}

static void
WriteCrashReport(FILE *f, EXCEPTION_POINTERS *info)
{
	fprintf(f, "# crash: exception 0x%08lX at frame %d\n",
		(unsigned long)info->ExceptionRecord->ExceptionCode, gFrame);
	WriteStack(f);
}

static LONG WINAPI
HarnessCrashFilter(EXCEPTION_POINTERS *info)
{
	FILE *f = fopen("harness_crash.txt", "w");
	if(f){
		WriteCrashReport(f, info);
		fclose(f);
	}
	if(gTrace){
		WriteCrashReport(gTrace, info);
		fclose(gTrace);
		gTrace = nil;
	}
	return EXCEPTION_EXECUTE_HANDLER; // terminate without the Windows error dialog
}
#endif

// Diagnostic hook: game code can call this to log where a suspicious value came from.
void
CHarness::ReportStack(const char *why)
{
	FILE *f = fopen("harness_stack.txt", "a");
	if(f == nil)
		return;
	fprintf(f, "# frame %d: %s\n", gFrame, why);
#ifdef _WIN32
	WriteStack(f);
#endif
	fclose(f);
}

// ---------------------------------------------------------------------------

bool
CHarness::ParseArg(const char *arg)
{
	if(strcmp(arg, "-harness") == 0){
		bActive = true;
#ifdef _WIN32
		GetCurrentDirectoryA(sizeof(gStartDir), gStartDir);
#endif
#ifdef LIBRW
		gHarnessDraw2DHook = HarnessDraw2D;
#endif
#ifdef _WIN32
		SetUnhandledExceptionFilter(HarnessCrashFilter);
		SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
#endif
		// The settings file was already read when the command line is parsed.
		ApplySettingsOverrides();
		return true;
	}
	if(strncmp(arg, "-harness-seed=", 14) == 0){
		gSeed = (uint32)strtoul(arg + 14, nil, 10);
		return true;
	}
	if(strncmp(arg, "-harness-frames=", 16) == 0){
		gMaxFrames = atoi(arg + 16);
		return true;
	}
	if(strncmp(arg, "-harness-trace=", 15) == 0){
		strncpy(gTracePath, arg + 15, sizeof(gTracePath) - 1);
		gTracePath[sizeof(gTracePath) - 1] = '\0';
		return true;
	}
	if(strncmp(arg, "-harness-load=", 14) == 0){
		gLoadSlot = atoi(arg + 14);
		return true;
	}
	if(strcmp(arg, "-harness-idle") == 0){
		gIdle = true;
		return true;
	}
	if(strncmp(arg, "-harness-scenario=", 18) == 0){
		strncpy(gScenario, arg + 18, sizeof(gScenario) - 1);
		gScenario[sizeof(gScenario) - 1] = '\0';
		gFreeroam = strstr(gScenario, "freeroam") != nil;
		return true;
	}
	if(strncmp(arg, "-harness-scenario-frame=", 24) == 0){
		gScenarioFrame = atoi(arg + 24);
		return true;
	}
	if(strncmp(arg, "-harness-expect=", 16) == 0){
		strncpy(gExpectPath, arg + 16, sizeof(gExpectPath) - 1);
		return true;
	}
	if(strncmp(arg, "-harness-userfiles=", 19) == 0){
		strncpy(gUserFilesArg, arg + 19, sizeof(gUserFilesArg) - 1);
		return true;
	}
	if(strncmp(arg, "-harness-stack-draw=", 20) == 0){
		sscanf(arg + 20, "%d:%d", &gStackDrawFrame, &gStackDrawCall);
		return true;
	}
	if(strncmp(arg, "-harness-jitter=", 16) == 0){
		gJitterMaxMs = atoi(arg + 16);
		return true;
	}
	if(strcmp(arg, "-harness-detail") == 0){
		gWantDetail = true;
		return true;
	}
	return false;
}

void
CHarness::ApplySettingsOverrides(void)
{
	if(!bActive)
		return;
	FrontEndMenuManager.m_nPrefsWidth = 1280;
	FrontEndMenuManager.m_nPrefsHeight = 720;
	FrontEndMenuManager.m_nPrefsDepth = 32;
	FrontEndMenuManager.m_nPrefsWindowed = 1;
	CMenuManager::m_PrefsFrameLimiter = false;
	CMenuManager::m_PrefsVsync = 0;
	CMenuManager::m_PrefsVsyncDisp = 0;
	CMenuManager::m_PrefsSfxVolume = 0;
	CMenuManager::m_PrefsMusicVolume = 0;
	CMenuManager::m_ControlMethod = CONTROL_STANDARD;
	gbNoMovies = true;
}

bool
CHarness::PrepareStart(void)
{
	// "Start new game" or "Load game" in the menu restarts through here: keep the run
	// (trace, frame count, input generator) going and honour a menu load request.
	static bool started;
	if(started)
		return FrontEndMenuManager.m_bWantToLoad;
	started = true;
	if(gExpectPath[0])
		LoadExpect();

	gFrame = 0;
	gGen.s = 0x9E3779B97F4A7C15ULL ^ ((uint64)gSeed * 0xBF58476D1CE4E5B9ULL);
	if(gGen.s == 0)
		gGen.s = 1;
	gGen.remaining = 0;

	gTrace = fopen(gTracePath, "w");
	if(gTrace){
		fprintf(gTrace, "# re3 replay harness sha=%s seed=%u frames=%d load=%d idle=%d scenario=%s@%d\n",
			g_GIT_SHA1, gSeed, gMaxFrames, gLoadSlot, gIdle ? 1 : 0, gScenario[0] ? gScenario : "none", gScenarioFrame);
#ifdef _WIN32
		// The tools start the game with ALSOFT_DRIVERS=null (OpenAL's no-output backend):
		// traces made with a real sound device are not comparable with them.
		char drivers[32] = "";
		GetEnvironmentVariableA("ALSOFT_DRIVERS", drivers, sizeof(drivers));
		if(strcmp(drivers, "null") != 0)
			fprintf(gTrace, "# warning: real audio device (ALSOFT_DRIVERS is not null)\n");
#endif
		fprintf(gTrace, "frame,time_ms,rng,peds,vehicles,objects,player,script,camera,world,audio,draw2d,n_peds,n_vehicles,n_objects,n_audio,n_draw2d,px,py,pz\n");
	}

	if(gWantDetail){
		char detailPath[280];
		sprintf(detailPath, "%s.detail.txt", gTracePath);
		gDetail = fopen(detailPath, "w");
	}

	if(gLoadSlot > 0 && CheckSlotDataValid(gLoadSlot - 1)){
		FrontEndMenuManager.m_nCurrSaveSlot = gLoadSlot - 1;
		FrontEndMenuManager.m_bWantToLoad = true;
		return true;
	}
	if(gLoadSlot > 0)
		debug("harness: save slot %d is not valid, starting a new game\n", gLoadSlot);
	return false;
}

void
CHarness::OnGameInitialise(void)
{
	mysrand(gSeed);
#ifdef USE_DEBUG_SCRIPT_LOADER
	CTheScripts::ScriptToLoad = gFreeroam ? 1 : 0; // 1 = data/main_freeroam.scm, no missions
#endif
}

void
CHarness::InjectInput(void)
{
	CPad *pad = CPad::GetPad(0);
	CControllerState genPad;
	CMouseControllerState genMouse;
	GenFrame(genPad, genMouse);

	pad->PCTempKeyState = genPad;
	pad->PCTempJoyState.Clear();
	pad->PCTempMouseState.Clear();
	CPad::OldMouseControllerState = CPad::NewMouseControllerState;
	CPad::NewMouseControllerState = genMouse;
	CPad::PCTempMouseControllerState = genMouse;
	memset(&CPad::OldKeyState, 0, sizeof(CPad::OldKeyState));
	memset(&CPad::NewKeyState, 0, sizeof(CPad::NewKeyState));
	memset(&CPad::TempKeyState, 0, sizeof(CPad::TempKeyState));
	CPad::IsAffectedByController = false;
	Jitter();
}

void
CHarness::AfterStreamingUpdate(void)
{
	Jitter();
	CStreaming::LoadAllRequestedModels(false);
	Jitter();
}

void
CHarness::EndFrame(void)
{
	Jitter();
	if(gScenario[0] && gFrame == gScenarioFrame)
		ApplyScenario();

	int32 nPeds, nVehicles, nObjects;
	uint64 peds = HashPeds(nPeds);
	uint64 vehicles = HashVehicles(nVehicles);
	uint64 objects = HashObjects(nObjects);
	uint64 player = HashPlayer();
	uint64 script = HashScript();
	uint64 camera = HashCamera();
	uint64 world = HashWorld();
	CVector pos(0.0f, 0.0f, 0.0f);
	if(FindPlayerPed())
		pos = FindPlayerPed()->GetPosition();

	char line[512];
	snprintf(line, sizeof(line), "%d,%u,%016llx,%016llx,%016llx,%016llx,%016llx,%016llx,%016llx,%016llx,%016llx,%016llx,%d,%d,%d,%d,%d,%.3f,%.3f,%.3f\n",
		gFrame, CTimer::GetTimeInMilliseconds(), (unsigned long long)myrand_seed,
		(unsigned long long)peds, (unsigned long long)vehicles, (unsigned long long)objects,
		(unsigned long long)player, (unsigned long long)script, (unsigned long long)camera,
		(unsigned long long)world, (unsigned long long)gAudioHash.h, (unsigned long long)gDrawHash.h,
		nPeds, nVehicles, nObjects, gAudioRequests, gDrawCalls, pos.x, pos.y, pos.z);
	if(gTrace){
		fputs(line, gTrace);
		fflush(gTrace); // keep the trace readable up to the last frame if the game crashes
	}
	if(gExpectLoaded && (gFrame >= (int32)gExpect.size() || strcmp(line, gExpect[gFrame].c_str()) != 0)){
		// -harness-expect: stop at the first frame that differs from the baseline trace
		if(gTrace)
			fprintf(gTrace, "# diverged at frame %d\n", gFrame);
		Shutdown();
		RsGlobal.quit = TRUE;
		gFrame++;
		return;
	}
	gAudioHash = Hasher();
	gAudioRequests = 0;
	gDrawHash = Hasher();
	gDrawCalls = 0;
	WriteScriptDetail();

	gFrame++;
	if(gFrame >= gMaxFrames){
		Shutdown();
		RsGlobal.quit = TRUE;
	}else if(RsGlobal.quit && gTrace){
		// the game quit by itself (the menu's Quit): a legitimate, comparable end
		fprintf(gTrace, "# game quit at frame %d\n", gFrame);
		Shutdown();
	}
}

const char *
CHarness::GetUserFilesFolder(void)
{
	static char folder[260];
	if(folder[0] == '\0'){
#ifdef _WIN32
		// absolute, from the start-up directory: re3 changes the working directory later
		char base[280];
		snprintf(base, sizeof(base), "%s\\harness_userfiles", gStartDir);
		if(gUserFilesArg[0] && (gUserFilesArg[1] == ':' || gUserFilesArg[0] == '\\' || gUserFilesArg[0] == '/'))
			snprintf(folder, sizeof(folder), "%s", gUserFilesArg);
		else if(gUserFilesArg[0])
			snprintf(folder, sizeof(folder), "%s\\%s", gStartDir, gUserFilesArg);
		else{
			CreateDirectoryA(base, nil);
			snprintf(folder, sizeof(folder), "%s\\p%lu", base, (unsigned long)GetCurrentProcessId());
		}
#else
		strcpy(folder, gUserFilesArg[0] ? gUserFilesArg : "harness_userfiles");
#endif
#ifdef _WIN32
		CreateDirectoryA(folder, nil);
#endif
	}
	return folder;
}

void
CHarness::Shutdown(void)
{
	if(gTrace){
		// the process exit code at shutdown is not reliable; compare.py checks this marker
		fprintf(gTrace, "# end frames=%d\n", gFrame);
		fclose(gTrace);
		gTrace = nil;
	}
	if(gDetail){
		fclose(gDetail);
		gDetail = nil;
	}
}

#endif
