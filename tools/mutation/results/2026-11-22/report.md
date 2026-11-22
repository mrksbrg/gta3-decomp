# Mutation results (Mull profile: cxx_default + cxx_remove_void_call)

| File | Killed | Survived | No coverage | Compile errors | Score | Covered score |
| --- | --- | --- | --- | --- | --- | --- |
| src/audio/AudioLogic.cpp | 120 | 46 | 134 | 0 | 40.0% | 72.3% |
| src/control/CarCtrl.cpp | 189 | 91 | 20 | 0 | 63.0% | 67.5% |
| src/core/Cam.cpp | 71 | 33 | 196 | 0 | 23.7% | 68.3% |
| src/core/Frontend.cpp | 39 | 26 | 235 | 0 | 13.0% | 60.0% |
| src/peds/Ped.cpp | 143 | 87 | 70 | 0 | 47.7% | 62.2% |
| src/peds/PedAI.cpp | 83 | 49 | 168 | 0 | 27.7% | 62.9% |
| src/vehicles/Automobile.cpp | 117 | 87 | 96 | 0 | 39.0% | 57.4% |
| **all** | 762 | 419 | 919 | 0 | **36.3%** | **64.5%** |

## Functions (covered score; ImageMagick gate: ready >= 90%, careful 75-90%, not ready < 75%)

| File | Function | Killed | Survived | No coverage | Covered score | Verdict |
| --- | --- | --- | --- | --- | --- | --- |
| AudioLogic.cpp | cAudioManager::ProcessPedOneShots | 14 | 1 | 7 | 93% | ready |
| AudioLogic.cpp | cAudioManager::ProcessPlayersVehicleEngine | 13 | 3 | 2 | 81% | careful |
| AudioLogic.cpp | cAudioManager::ProcessVehicleEngine | 12 | 1 | 0 | 92% | ready |
| AudioLogic.cpp | cAudioManager::ProcessBoatEngine | 9 | 1 | 0 | 90% | ready |
| AudioLogic.cpp | cAudioManager::ProcessVehicleOneShots | 5 | 0 | 3 | 100% | ready |
| AudioLogic.cpp | cAudioManager::ProcessCesna | 6 | 1 | 1 | 86% | careful |
| AudioLogic.cpp | cAudioManager::ProcessOneShotScriptObject | 4 | 0 | 3 | 100% | too few |
| AudioLogic.cpp | cAudioManager::ProcessGarages | 0 | 1 | 5 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessWeather | 5 | 0 | 0 | 100% | ready |
| AudioLogic.cpp | cAudioManager::ProcessHelicopter | 2 | 2 | 1 | 50% | too few |
| AudioLogic.cpp | cPedComments::Process | 4 | 1 | 0 | 80% | careful |
| AudioLogic.cpp | cAudioManager::ProcessMissionAudio | 0 | 0 | 4 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetFanFemaleTalkSfx | 0 | 0 | 4 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessJumbo | 1 | 1 | 2 | 50% | too few |
| AudioLogic.cpp | cAudioManager::PreTerminateGameSpecificShutdown | 0 | 4 | 0 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessHomeScriptObject | 0 | 2 | 2 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetVehicleDriveWheelSkidValue | 3 | 1 | 0 | 75% | too few |
| AudioLogic.cpp | cAudioManager::ProcessBridgeOneShots | 0 | 3 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetWhiteFemaleProstituteTalkSfx | 0 | 0 | 3 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessVehicleSkidding | 3 | 0 | 0 | 100% | too few |
| AudioLogic.cpp | cAudioManager::ProcessVehicle | 2 | 1 | 0 | 67% | too few |
| AudioLogic.cpp | cAudioManager::ProcessRainOnVehicle | 2 | 1 | 0 | 67% | too few |
| AudioLogic.cpp | cAudioManager::ProcessJumboAccel | 0 | 0 | 3 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessSpecial | 0 | 3 | 0 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessPedHeadphones | 2 | 1 | 0 | 67% | too few |
| AudioLogic.cpp | cAudioManager::GetFanMaleTalkSfx | 0 | 0 | 3 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessJumboLanding | 0 | 0 | 3 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetBlackBusinessFemaleTalkSfx | 0 | 0 | 3 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessShopScriptObject | 0 | 0 | 3 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessEntity | 1 | 2 | 0 | 33% | too few |
| AudioLogic.cpp | cAudioManager::ProcessPornCinema | 0 | 0 | 3 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessPoliceCellBeatingScriptObject | 0 | 0 | 3 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessDocksScriptObject | 0 | 1 | 2 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessModelCarEngine | 0 | 0 | 3 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessFrontEnd | 2 | 1 | 0 | 67% | too few |
| AudioLogic.cpp | cAudioManager::GetSupermodelMaleTalkSfx | 0 | 0 | 3 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessBoatMovingOverWater | 3 | 0 | 0 | 100% | too few |
| AudioLogic.cpp | cAudioManager::HasAirBrakes | 2 | 0 | 0 | 100% | too few |
| AudioLogic.cpp | cAudioManager::ProcessBridgeMotor | 0 | 0 | 2 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetSwatTalkSfx | 0 | 0 | 2 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetEightBallTalkSfx | 0 | 0 | 2 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessFires | 0 | 1 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::SetupJumboRumbleSound | 0 | 0 | 2 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessVehicleDoors | 2 | 0 | 0 | 100% | too few |
| AudioLogic.cpp | cAudioManager::ProcessAirportScriptObject | 0 | 1 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessAirBrakes | 1 | 1 | 0 | 50% | too few |
| AudioLogic.cpp | cAudioManager::ProcessReverb | 0 | 2 | 0 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ResetAudioLogicTimers | 1 | 1 | 0 | 50% | too few |
| AudioLogic.cpp | cAudioManager::GetColumbianTalkSfx | 0 | 0 | 2 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetLittleItalyFemaleOldTalkSfx | 0 | 0 | 2 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessVehicleRoadNoise | 2 | 0 | 0 | 100% | too few |
| AudioLogic.cpp | cAudioManager::ProcessJumboTakeOff | 0 | 0 | 2 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetFemaleNo3TalkSfx | 0 | 0 | 2 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessCrane | 0 | 0 | 2 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetDistanceSquared | 2 | 0 | 0 | 100% | too few |
| AudioLogic.cpp | cAudioManager::GetWhiteConstructionWorkerTalkSfx | 0 | 0 | 2 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessLoopingScriptObject | 1 | 1 | 0 | 50% | too few |
| AudioLogic.cpp | cAudioManager::GetLittleItalyMaleTalkSfx | 0 | 0 | 2 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetMedicTalkSfx | 0 | 0 | 2 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessSawMillScriptObject | 0 | 0 | 2 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetYardieTalkSfx | 0 | 0 | 2 | 0% | too few |
| AudioLogic.cpp | cAudioManager::SetupJumboTaxiSound | 0 | 0 | 2 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessReverseGear | 2 | 0 | 0 | 100% | too few |
| AudioLogic.cpp | cAudioManager::GetMistyTalkSfx | 0 | 0 | 2 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetTriadTalkSfx | 0 | 0 | 2 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetDiabloTalkSfx | 0 | 0 | 2 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetGenericMaleTalkSfx | 1 | 0 | 1 | 100% | too few |
| AudioLogic.cpp | cAudioManager::ProcessPlane | 0 | 2 | 0 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetWhiteWorkerMaleTalkSfx | 0 | 0 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessExplosions | 1 | 0 | 0 | 100% | too few |
| AudioLogic.cpp | cAudioManager::SetupJumboWhineSound | 0 | 0 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::SetupJumboEngineSound | 0 | 1 | 0 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetStewardMaleTalkSfx | 0 | 0 | 1 | 0% | too few |
| AudioLogic.cpp | cPedComments::Add | 1 | 0 | 0 | 100% | too few |
| AudioLogic.cpp | cAudioManager::GetPimpTalkSfx | 0 | 0 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessVehicleSirenOrAlarm | 1 | 0 | 0 | 100% | too few |
| AudioLogic.cpp | cAudioManager::ProcessWaterCannon | 0 | 1 | 0 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetShopperFemaleTalkSfx | 0 | 0 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::SetupPedComments | 0 | 0 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessCinemaScriptObject | 0 | 0 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetBlackFatFemaleTalkSfx | 1 | 0 | 0 | 100% | too few |
| AudioLogic.cpp | cAudioManager::ProcessBridge | 1 | 0 | 0 | 100% | too few |
| AudioLogic.cpp | cAudioManager::ProcessPed | 1 | 0 | 0 | 100% | too few |
| AudioLogic.cpp | cAudioManager::ProcessFireHydrant | 0 | 0 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::PreloadMissionAudio | 0 | 1 | 0 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetSupermodelFemaleTalkSfx | 0 | 0 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetArmyTalkSfx | 0 | 0 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetBlackFatMaleTalkSfx | 1 | 0 | 0 | 100% | too few |
| AudioLogic.cpp | cAudioManager::ProcessEngineDamage | 1 | 0 | 0 | 100% | too few |
| AudioLogic.cpp | cAudioManager::GetCopTalkSfx | 1 | 0 | 0 | 100% | too few |
| AudioLogic.cpp | cAudioManager::GetStudentFemaleTalkSfx | 0 | 0 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetFBITalkSfx | 0 | 0 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetYakuzaTalkSfx | 0 | 0 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetPhrase | 1 | 0 | 0 | 100% | too few |
| AudioLogic.cpp | cAudioManager::GetScumMaleTalkSfx | 0 | 0 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessWorkShopScriptObject | 0 | 0 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetWhiteFatMaleTalkSfx | 1 | 0 | 0 | 100% | too few |
| AudioLogic.cpp | cAudioManager::ProcessVehicleHorn | 1 | 0 | 0 | 100% | too few |
| AudioLogic.cpp | cAudioManager::GetScumFemaleTalkSfx | 0 | 0 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetSecurityGuardTalkSfx | 0 | 0 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetChinatownMaleYoungTalkSfx | 0 | 0 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetHoodTalkSfx | 0 | 0 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::PostInitialiseGameSpecificSetup | 0 | 1 | 0 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetHospitalFemaleTalkSfx | 0 | 0 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetBusinessMaleYoungTalkSfx | 0 | 0 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessLaunderetteScriptObject | 0 | 0 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::SetupJumboFlySound | 0 | 1 | 0 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessTrainNoise | 1 | 0 | 0 | 100% | too few |
| AudioLogic.cpp | cAudioManager::GetBlackDockerMaleTalkSfx | 0 | 0 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetBlackProjectMaleTalkSfx | 0 | 0 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetBlackFemaleProstituteTalkSfx | 0 | 0 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessBridgeWarning | 0 | 0 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetWhiteDockerMaleTalkSfx | 0 | 0 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetChinatownFemaleOldTalkSfx | 0 | 0 | 1 | 0% | too few |
| CarCtrl.cpp | CCarCtrl::GenerateOneRandomCar | 35 | 9 | 0 | 80% | careful |
| CarCtrl.cpp | CCarCtrl::TestCollisionBetween2MovingRects | 23 | 3 | 0 | 88% | careful |
| CarCtrl.cpp | CCarCtrl::PickNextNodeRandomly | 19 | 6 | 0 | 76% | careful |
| CarCtrl.cpp | CCarCtrl::SteerAICarWithPhysicsFollowPath | 17 | 3 | 0 | 85% | careful |
| CarCtrl.cpp | CCarCtrl::PickNextNodeToChaseCar | 4 | 10 | 1 | 29% | not ready |
| CarCtrl.cpp | CCarCtrl::ChooseModel | 12 | 0 | 0 | 100% | ready |
| CarCtrl.cpp | CCarCtrl::SlowCarDownForPedsSectorList | 5 | 6 | 0 | 45% | not ready |
| CarCtrl.cpp | CCarCtrl::SlowCarDownForOtherCar | 1 | 6 | 2 | 14% | not ready |
| CarCtrl.cpp | CCarCtrl::PickNextNodeToFollowPath | 2 | 7 | 0 | 22% | not ready |
| CarCtrl.cpp | CCarCtrl::SteerAICarWithPhysics | 4 | 0 | 4 | 100% | too few |
| CarCtrl.cpp | CCarCtrl::GenerateEmergencyServicesCar | 0 | 6 | 2 | 0% | not ready |
| CarCtrl.cpp | CCarCtrl::UpdateCarOnRails | 5 | 2 | 0 | 71% | not ready |
| CarCtrl.cpp | CCarCtrl::FindAngleToWeaveThroughTraffic | 5 | 2 | 0 | 71% | not ready |
| CarCtrl.cpp | CCarCtrl::DragCarToPoint | 5 | 1 | 0 | 83% | careful |
| CarCtrl.cpp | CCarCtrl::SteerAIBoatWithPhysicsHeadingForTarget | 0 | 0 | 6 | 0% | too few |
| CarCtrl.cpp | CCarCtrl::FindPathDirection | 5 | 0 | 0 | 100% | ready |
| CarCtrl.cpp | CCarCtrl::SteerAICarWithPhysics_OnlyMission | 3 | 2 | 0 | 60% | not ready |
| CarCtrl.cpp | CCarCtrl::WeaveForOtherCar | 3 | 2 | 0 | 60% | not ready |
| CarCtrl.cpp | CCarCtrl::FindMaximumSpeedForThisCarInTraffic | 4 | 1 | 0 | 80% | careful |
| CarCtrl.cpp | CCarCtrl::ScanForPedDanger | 3 | 1 | 0 | 75% | too few |
| CarCtrl.cpp | CCarCtrl::WeaveThroughObjectsSectorList | 2 | 2 | 0 | 50% | too few |
| CarCtrl.cpp | CCarCtrl::MapCouldMoveInThisArea | 0 | 3 | 1 | 0% | too few |
| CarCtrl.cpp | CCarCtrl::PossiblyRemoveVehicle | 1 | 3 | 0 | 25% | too few |
| CarCtrl.cpp | CCarCtrl::WeaveThroughPedsSectorList | 4 | 0 | 0 | 100% | too few |
| CarCtrl.cpp | CCarCtrl::GenerateRandomCars | 3 | 0 | 0 | 100% | too few |
| CarCtrl.cpp | CCarCtrl::WeaveForObject | 3 | 0 | 0 | 100% | too few |
| CarCtrl.cpp | CCarCtrl::SlowCarOnRailsDownForTrafficAndLights | 1 | 2 | 0 | 33% | too few |
| CarCtrl.cpp | CCarCtrl::RegisterVehicleOfInterest | 0 | 3 | 0 | 0% | too few |
| CarCtrl.cpp | CCarCtrl::FindLinksToGoWithTheseNodes | 1 | 2 | 0 | 33% | too few |
| CarCtrl.cpp | CCarCtrl::WeaveForPed | 3 | 0 | 0 | 100% | too few |
| CarCtrl.cpp | CCarCtrl::WeaveThroughCarsSectorList | 2 | 1 | 0 | 67% | too few |
| CarCtrl.cpp | CCarCtrl::SteerAICarWithPhysicsTryingToBlockTarget_Stop | 2 | 1 | 0 | 67% | too few |
| CarCtrl.cpp | CCarCtrl::Init | 1 | 2 | 0 | 33% | too few |
| CarCtrl.cpp | CCarCtrl::SlowCarDownForCarsSectorList | 2 | 1 | 0 | 67% | too few |
| CarCtrl.cpp | CCarCtrl::SteerAICarWithPhysicsHeadingForTarget | 2 | 0 | 0 | 100% | too few |
| CarCtrl.cpp | CCarCtrl::SteerAIBoatWithPhysics | 0 | 0 | 2 | 0% | too few |
| CarCtrl.cpp | CCarCtrl::JoinCarWithRoadSystemGotoCoors | 2 | 0 | 0 | 100% | too few |
| CarCtrl.cpp | CCarCtrl::GenerateOneEmergencyServicesCar | 0 | 0 | 2 | 0% | too few |
| CarCtrl.cpp | CCarCtrl::JoinCarWithRoadSystem | 1 | 1 | 0 | 50% | too few |
| CarCtrl.cpp | CCarCtrl::ChooseCarModel | 1 | 0 | 0 | 100% | too few |
| CarCtrl.cpp | CCarCtrl::UpdateCarCount | 0 | 1 | 0 | 0% | too few |
| CarCtrl.cpp | CCarCtrl::RemoveFromInterestingVehicleList | 1 | 0 | 0 | 100% | too few |
| CarCtrl.cpp | CCarCtrl::RemoveDistantCars | 1 | 0 | 0 | 100% | too few |
| CarCtrl.cpp | CCarCtrl::ChoosePoliceCarModel | 0 | 1 | 0 | 0% | too few |
| CarCtrl.cpp | CCarCtrl::IsThisVehicleInteresting | 1 | 0 | 0 | 100% | too few |
| CarCtrl.cpp | CCarCtrl::ThisRoadObjectCouldMove | 0 | 1 | 0 | 0% | too few |
| Cam.cpp | CCam::Process_FollowCar_SA | 0 | 0 | 45 | 0% | too few |
| Cam.cpp | CCam::Process_FollowPed | 0 | 0 | 25 | 0% | too few |
| Cam.cpp | FindSplinePathPositionVector | 14 | 1 | 4 | 93% | ready |
| Cam.cpp | CCam::Process_BehindBoat | 8 | 6 | 0 | 57% | not ready |
| Cam.cpp | CCam::Process | 3 | 3 | 5 | 50% | not ready |
| Cam.cpp | CCam::WorkOutCamHeight | 8 | 0 | 2 | 100% | ready |
| Cam.cpp | CCam::ProcessSpecialHeightRoutines | 0 | 10 | 0 | 0% | not ready |
| Cam.cpp | CCam::Process_Debug | 0 | 0 | 9 | 0% | too few |
| Cam.cpp | CCam::Process_1stPerson | 1 | 0 | 8 | 100% | too few |
| Cam.cpp | CCam::Process_1rstPersonPedOnPC | 0 | 0 | 9 | 0% | too few |
| Cam.cpp | CCam::Process_Sniper | 0 | 0 | 8 | 0% | too few |
| Cam.cpp | CCam::Process_FollowPed_Rotation | 0 | 0 | 7 | 0% | too few |
| Cam.cpp | CCam::Process_FollowPed_WithBinding | 0 | 0 | 7 | 0% | too few |
| Cam.cpp | CCam::Process_Syphon | 0 | 0 | 6 | 0% | too few |
| Cam.cpp | CCam::ProcessPedsDeadBaby | 5 | 1 | 0 | 83% | careful |
| Cam.cpp | CCam::Process_ReactionCam | 0 | 0 | 6 | 0% | too few |
| Cam.cpp | CCam::Process_FollowPedWithMouse | 3 | 2 | 1 | 60% | not ready |
| Cam.cpp | CCam::Process_FlyBy | 1 | 2 | 2 | 33% | too few |
| Cam.cpp | CCam::Process_TopDownPed | 3 | 2 | 0 | 60% | not ready |
| Cam.cpp | CCam::Process_Rocket | 0 | 0 | 5 | 0% | too few |
| Cam.cpp | CCam::ProcessArrestCamTwo | 3 | 2 | 0 | 60% | not ready |
| Cam.cpp | CCam::Process_BehindCar | 0 | 0 | 5 | 0% | too few |
| Cam.cpp | CCam::WorkOutCamHeightWeeCar | 0 | 0 | 4 | 0% | too few |
| Cam.cpp | CCam::LookRight | 0 | 0 | 4 | 0% | too few |
| Cam.cpp | CCam::Process_Syphon_Crim_In_Front | 0 | 0 | 4 | 0% | too few |
| Cam.cpp | CCam::Cam_On_A_String_Unobscured | 3 | 1 | 0 | 75% | too few |
| Cam.cpp | CCam::Process_M16_1stPerson | 0 | 0 | 4 | 0% | too few |
| Cam.cpp | CCam::LookBehind | 0 | 0 | 4 | 0% | too few |
| Cam.cpp | CCam::Process_Cam_On_A_String | 4 | 0 | 0 | 100% | too few |
| Cam.cpp | CCam::RotCamIfInFrontCar | 4 | 0 | 0 | 100% | too few |
| Cam.cpp | CCam::FixCamIfObscured | 2 | 0 | 1 | 100% | too few |
| Cam.cpp | FindSplinePathPositionFloat | 1 | 0 | 2 | 100% | too few |
| Cam.cpp | CCam::Process_TopDown | 0 | 0 | 3 | 0% | too few |
| Cam.cpp | CCam::DoAverageOnVector | 2 | 1 | 0 | 67% | too few |
| Cam.cpp | WellBufferMe | 3 | 0 | 0 | 100% | too few |
| Cam.cpp | CCam::Process_Bill | 0 | 0 | 3 | 0% | too few |
| Cam.cpp | CCam::Process_ModelView | 0 | 0 | 2 | 0% | too few |
| Cam.cpp | CCam::GetPedBetaAngleForClearView | 0 | 0 | 2 | 0% | too few |
| Cam.cpp | CCam::LookLeft | 2 | 0 | 0 | 100% | too few |
| Cam.cpp | CCam::Process_Fight_Cam | 0 | 0 | 2 | 0% | too few |
| Cam.cpp | CCam::FixCamWhenObscuredByVehicle | 1 | 0 | 0 | 100% | too few |
| Cam.cpp | CCam::Process_SpecialFixedForSyphon | 0 | 0 | 1 | 0% | too few |
| Cam.cpp | CCam::Process_Cam_On_Train_Roof | 0 | 0 | 1 | 0% | too few |
| Cam.cpp | CCam::Process_Chris_With_Binding_PlusRotation | 0 | 0 | 1 | 0% | too few |
| Cam.cpp | CCam::Process_Editor | 0 | 0 | 1 | 0% | too few |
| Cam.cpp | CCam::ClipIfPedInFrontOfPlayer | 0 | 1 | 0 | 0% | too few |
| Cam.cpp | CCam::Process_Circle | 0 | 0 | 1 | 0% | too few |
| Cam.cpp | CCam::ProcessArrestCamOne | 0 | 0 | 1 | 0% | too few |
| Cam.cpp | CCam::AvoidWallsTopDownPed | 0 | 1 | 0 | 0% | too few |
| Cam.cpp | CCam::Process_Fixed | 0 | 0 | 1 | 0% | too few |
| Frontend.cpp | CMenuManager::PrintController | 0 | 0 | 52 | 0% | too few |
| Frontend.cpp | CMenuManager::ProcessButtonPresses | 11 | 7 | 30 | 61% | not ready |
| Frontend.cpp | CMenuManager::PrintMap | 0 | 0 | 28 | 0% | too few |
| Frontend.cpp | CMenuManager::Draw | 9 | 2 | 14 | 82% | careful |
| Frontend.cpp | CMenuManager::DrawPlayerSetupScreen | 0 | 0 | 13 | 0% | too few |
| Frontend.cpp | CMenuManager::LoadAllTextures | 4 | 5 | 3 | 44% | not ready |
| Frontend.cpp | CMenuManager::DrawControllerBound | 0 | 0 | 11 | 0% | too few |
| Frontend.cpp | CMenuManager::ProcessList | 0 | 0 | 11 | 0% | too few |
| Frontend.cpp | CMenuManager::ProcessOnOffMenuOptions | 0 | 0 | 9 | 0% | too few |
| Frontend.cpp | CMenuManager::ConstructStatLine | 0 | 0 | 8 | 0% | too few |
| Frontend.cpp | CMenuManager::DisplayHelperText | 0 | 0 | 7 | 0% | too few |
| Frontend.cpp | CMenuManager::Process | 1 | 2 | 4 | 33% | too few |
| Frontend.cpp | CMenuManager::LoadController | 3 | 2 | 1 | 60% | not ready |
| Frontend.cpp | CMenuManager::DrawControllerScreenExtraText | 0 | 0 | 6 | 0% | too few |
| Frontend.cpp | CMenuManager::PrintStats | 0 | 0 | 5 | 0% | too few |
| Frontend.cpp | CMenuManager::ThingsToDoBeforeGoingBack | 2 | 1 | 2 | 67% | too few |
| Frontend.cpp | CMenuManager::DrawControllerSetupScreen | 0 | 0 | 5 | 0% | too few |
| Frontend.cpp | CMenuManager::DrawFrontEndNormal | 3 | 0 | 1 | 100% | too few |
| Frontend.cpp | CMenuManager::UnloadTextures | 0 | 4 | 0 | 0% | too few |
| Frontend.cpp | CMenuManager::CheckCodesForControls | 0 | 0 | 4 | 0% | too few |
| Frontend.cpp | CMenuManager::PrintBriefs | 1 | 1 | 1 | 50% | too few |
| Frontend.cpp | CMenuManager::FilterOutColorMarkersFromString | 0 | 0 | 3 | 0% | too few |
| Frontend.cpp | CMenuManager::CheckHover | 0 | 0 | 3 | 0% | too few |
| Frontend.cpp | CMenuManager::InitialiseChangedLanguageSettings | 0 | 0 | 3 | 0% | too few |
| Frontend.cpp | CMenuManager::SwitchMenuOnAndOff | 1 | 1 | 0 | 50% | too few |
| Frontend.cpp | CMenuManager::MessageScreen | 0 | 0 | 2 | 0% | too few |
| Frontend.cpp | CMenuManager::DisplaySlider | 0 | 0 | 2 | 0% | too few |
| Frontend.cpp | CMenuManager::CheckSliderMovement | 0 | 0 | 2 | 0% | too few |
| Frontend.cpp | CMenuManager::LoadSettings | 0 | 1 | 1 | 0% | too few |
| Frontend.cpp | CMenuManager::WaitForUserCD | 0 | 0 | 1 | 0% | too few |
| Frontend.cpp | CMenuManager::DrawFrontEnd | 1 | 0 | 0 | 100% | too few |
| Frontend.cpp | CMenuManager::PageDownList | 0 | 0 | 1 | 0% | too few |
| Frontend.cpp | CMenuManager::PageUpList | 0 | 0 | 1 | 0% | too few |
| Frontend.cpp | CMenuManager::GetPreviousPageOption | 1 | 0 | 0 | 100% | too few |
| Frontend.cpp | CMenuManager::FadeIn | 1 | 0 | 0 | 100% | too few |
| Frontend.cpp | CMenuManager::ShutdownJustMenu | 1 | 0 | 0 | 100% | too few |
| Frontend.cpp | CMenuManager::PickNewPlayerColour | 0 | 0 | 1 | 0% | too few |
| Ped.cpp | CPed::ProcessControl | 27 | 16 | 8 | 63% | not ready |
| Ped.cpp | CPed::SetDirectionToWalkAroundObject | 13 | 9 | 2 | 59% | not ready |
| Ped.cpp | CPed::Wait | 6 | 0 | 8 | 100% | ready |
| Ped.cpp | CPed::ScanForInterestingStuff | 6 | 1 | 7 | 86% | careful |
| Ped.cpp | CPed::SeekCar | 4 | 4 | 5 | 50% | not ready |
| Ped.cpp | CPed::Flee | 10 | 2 | 0 | 83% | careful |
| Ped.cpp | CPed::LookForInterestingNodes | 4 | 5 | 2 | 44% | not ready |
| Ped.cpp | CPed::ProcessBuoyancy | 4 | 4 | 0 | 50% | not ready |
| Ped.cpp | CPed::SetWaitState | 3 | 2 | 2 | 60% | not ready |
| Ped.cpp | CPed::PedSetInCarCB | 4 | 2 | 0 | 67% | not ready |
| Ped.cpp | CPed::FinishLaunchCB | 0 | 0 | 5 | 0% | too few |
| Ped.cpp | CPed::ScanForThreats | 1 | 3 | 1 | 25% | too few |
| Ped.cpp | CPed::ProcessEntityCollision | 2 | 3 | 0 | 40% | not ready |
| Ped.cpp | CPed::PreRender | 3 | 1 | 1 | 75% | too few |
| Ped.cpp | CPed::PedSetOutCarCB | 3 | 1 | 1 | 75% | too few |
| Ped.cpp | CPed::SetEvasiveDive | 1 | 1 | 2 | 50% | too few |
| Ped.cpp | CPed::SetEvasiveStep | 4 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::Avoid | 3 | 1 | 0 | 75% | too few |
| Ped.cpp | CPed::CanPedDriveOff | 1 | 3 | 0 | 25% | too few |
| Ped.cpp | CPed::Solicit | 0 | 0 | 4 | 0% | too few |
| Ped.cpp | CPed::PedSetDraggedOutCarCB | 2 | 0 | 1 | 100% | too few |
| Ped.cpp | CPed::FacePhone | 0 | 0 | 3 | 0% | too few |
| Ped.cpp | CPed::LookForSexyPeds | 3 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::UpdatePosition | 1 | 1 | 1 | 50% | too few |
| Ped.cpp | CPed::SetSeek | 3 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::Idle | 0 | 2 | 1 | 0% | too few |
| Ped.cpp | CPed::SetFlee | 1 | 2 | 0 | 33% | too few |
| Ped.cpp | CPed::WanderPath | 1 | 1 | 1 | 50% | too few |
| Ped.cpp | CPed::Seek | 0 | 3 | 0 | 0% | too few |
| Ped.cpp | CPed::GetLocalDirection | 1 | 1 | 0 | 50% | too few |
| Ped.cpp | CPed::SetAttackTimer | 1 | 1 | 0 | 50% | too few |
| Ped.cpp | CPed::SetRadioStation | 1 | 0 | 1 | 100% | too few |
| Ped.cpp | CPed::PlayFootSteps | 1 | 0 | 1 | 100% | too few |
| Ped.cpp | CPed::PedEvadeCB | 2 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::CanPedReturnToState | 2 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::~CPed | 2 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::SortPeds | 2 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::SetInTheAir | 0 | 1 | 1 | 0% | too few |
| Ped.cpp | CPed::SetGetUp | 1 | 1 | 0 | 50% | too few |
| Ped.cpp | CPed::SetMoveAnim | 1 | 1 | 0 | 50% | too few |
| Ped.cpp | CPed::LookForSexyCars | 1 | 1 | 0 | 50% | too few |
| Ped.cpp | CPed::MoveHeadToLook | 2 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::Render | 0 | 2 | 0 | 0% | too few |
| Ped.cpp | CPed::SetBuyIceCream | 0 | 0 | 2 | 0% | too few |
| Ped.cpp | CPed::CalculateNewVelocity | 2 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::WarpPedIntoCar | 0 | 2 | 0 | 0% | too few |
| Ped.cpp | CPed::Initialise | 1 | 1 | 0 | 50% | too few |
| Ped.cpp | CPed::CheckForExplosions | 0 | 0 | 1 | 0% | too few |
| Ped.cpp | CPed::RestorePreviousState | 0 | 0 | 1 | 0% | too few |
| Ped.cpp | CPed::ClearFall | 1 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::IsPointerValid | 1 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::SetFollowPath | 0 | 0 | 1 | 0% | too few |
| Ped.cpp | CPed::IsGangMember | 0 | 1 | 0 | 0% | too few |
| Ped.cpp | CPed::ClearFlee | 1 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::Save | 0 | 0 | 1 | 0% | too few |
| Ped.cpp | CPed::SetShootTimer | 1 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::SetCurrentWeapon | 0 | 1 | 0 | 0% | too few |
| Ped.cpp | CPed::CanStrafeOrMouseControl | 1 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::SetIdle | 1 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::SetFall | 0 | 1 | 0 | 0% | too few |
| Ped.cpp | CPed::WanderRange | 0 | 0 | 1 | 0% | too few |
| Ped.cpp | CPed::SetWanderPath | 0 | 0 | 1 | 0% | too few |
| Ped.cpp | CPed::UseGroundColModel | 1 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::PedLandCB | 1 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::SetModelIndex | 0 | 0 | 1 | 0% | too few |
| Ped.cpp | CPed::PossiblyFindBetterPosToSeekCar | 0 | 1 | 0 | 0% | too few |
| Ped.cpp | CPed::PedGetupCB | 1 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::CalculateNewOrientation | 1 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::SetDie | 0 | 0 | 1 | 0% | too few |
| Ped.cpp | CPed::SetAimFlag | 0 | 1 | 0 | 0% | too few |
| Ped.cpp | CPed::IsPedShootable | 0 | 1 | 0 | 0% | too few |
| Ped.cpp | CPed::GiveWeapon | 0 | 1 | 0 | 0% | too few |
| Ped.cpp | CPed::CPed | 1 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::BuildPedLists | 0 | 1 | 0 | 0% | too few |
| Ped.cpp | CPed::WillChat | 0 | 1 | 0 | 0% | too few |
| Ped.cpp | CPed::Mug | 0 | 0 | 1 | 0% | too few |
| Ped.cpp | CPed::Chat | 1 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::SetSeekCar | 1 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::Load | 0 | 0 | 1 | 0% | too few |
| PedAI.cpp | CPed::ProcessObjective | 28 | 7 | 66 | 80% | careful |
| PedAI.cpp | CPed::SetObjective | 1 | 3 | 11 | 25% | too few |
| PedAI.cpp | CPed::PedAnimDoorOpenCB | 4 | 3 | 5 | 57% | not ready |
| PedAI.cpp | CPed::LineUpPedWithCar | 9 | 2 | 1 | 82% | careful |
| PedAI.cpp | CPed::ReactToPointGun | 0 | 1 | 11 | 0% | too few |
| PedAI.cpp | CPed::UpdateFromLeader | 0 | 0 | 12 | 0% | too few |
| PedAI.cpp | CPed::SetExitCar | 4 | 2 | 5 | 67% | not ready |
| PedAI.cpp | CPed::PedSetQuickDraggedOutCarPositionCB | 6 | 0 | 4 | 100% | ready |
| PedAI.cpp | CPed::DuckAndCover | 4 | 1 | 2 | 80% | careful |
| PedAI.cpp | CPed::PedAnimGetInCB | 2 | 1 | 3 | 67% | too few |
| PedAI.cpp | CPed::WarpPedToNearLeaderOffScreen | 0 | 0 | 6 | 0% | too few |
| PedAI.cpp | CPed::RegisterThreatWithGangPeds | 2 | 0 | 4 | 100% | too few |
| PedAI.cpp | CPed::CanSeeEntity | 2 | 3 | 0 | 40% | not ready |
| PedAI.cpp | CPed::PedSetDraggedOutCarPositionCB | 0 | 0 | 4 | 0% | too few |
| PedAI.cpp | CPed::SelectGunIfArmed | 0 | 0 | 4 | 0% | too few |
| PedAI.cpp | CPed::PedAnimPullPedOutCB | 1 | 0 | 3 | 100% | too few |
| PedAI.cpp | CPed::SetCarJack_AllClear | 3 | 1 | 0 | 75% | too few |
| PedAI.cpp | CPed::SetEnterCar | 0 | 1 | 2 | 0% | too few |
| PedAI.cpp | CPed::ExitCar | 1 | 2 | 0 | 33% | too few |
| PedAI.cpp | CPed::SetAnimOffsetForEnterOrExitVehicle | 0 | 3 | 0 | 0% | too few |
| PedAI.cpp | CPed::SetEnterCar_AllClear | 1 | 2 | 0 | 33% | too few |
| PedAI.cpp | CPed::PedAnimDoorCloseCB | 0 | 0 | 3 | 0% | too few |
| PedAI.cpp | CPed::PedAnimAlignCB | 2 | 1 | 0 | 67% | too few |
| PedAI.cpp | CPed::SetCarJack | 3 | 0 | 0 | 100% | too few |
| PedAI.cpp | CPed::WarpPedToNearEntityOffScreen | 0 | 0 | 3 | 0% | too few |
| PedAI.cpp | CPed::SetExitTrain | 0 | 0 | 3 | 0% | too few |
| PedAI.cpp | CPed::ReactToAttack | 0 | 3 | 0 | 0% | too few |
| PedAI.cpp | CPed::PedAnimStepOutCarCB | 1 | 0 | 1 | 100% | too few |
| PedAI.cpp | CPed::SetExitBoat | 0 | 1 | 1 | 0% | too few |
| PedAI.cpp | SelectClosestNodeForSeek | 0 | 0 | 2 | 0% | too few |
| PedAI.cpp | CPed::GetLocalPositionToOpenCarDoor | 1 | 1 | 0 | 50% | too few |
| PedAI.cpp | CPed::BeingDraggedFromCar | 0 | 2 | 0 | 0% | too few |
| PedAI.cpp | CPed::GetNearestDoor | 1 | 1 | 0 | 50% | too few |
| PedAI.cpp | CPed::Duck | 1 | 1 | 0 | 50% | too few |
| PedAI.cpp | CPed::PedSetOutTrainCB | 0 | 0 | 2 | 0% | too few |
| PedAI.cpp | CPed::InformMyGangOfAttack | 0 | 0 | 1 | 0% | too few |
| PedAI.cpp | CPed::ClearLeader | 0 | 0 | 1 | 0% | too few |
| PedAI.cpp | CPed::PedSetInTrainCB | 0 | 0 | 1 | 0% | too few |
| PedAI.cpp | CPed::SetEnterTrain | 0 | 0 | 1 | 0% | too few |
| PedAI.cpp | CPed::PositionPedOutOfCollision | 1 | 0 | 0 | 100% | too few |
| PedAI.cpp | CPed::FindBestCoordsFromNodes | 0 | 0 | 1 | 0% | too few |
| PedAI.cpp | CPed::EnterCar | 0 | 1 | 0 | 0% | too few |
| PedAI.cpp | CPed::RestorePreviousObjective | 0 | 1 | 0 | 0% | too few |
| PedAI.cpp | CPed::GoToNearestDoor | 1 | 0 | 0 | 100% | too few |
| PedAI.cpp | CPed::SetDuck | 0 | 0 | 1 | 0% | too few |
| PedAI.cpp | CPed::SetBeingDraggedFromCar | 0 | 1 | 0 | 0% | too few |
| PedAI.cpp | AddYardieDoorSmoke | 0 | 0 | 1 | 0% | too few |
| PedAI.cpp | CPed::ClearDuck | 0 | 0 | 1 | 0% | too few |
| PedAI.cpp | CPed::IsRoomToBeCarJacked | 0 | 1 | 0 | 0% | too few |
| PedAI.cpp | CPed::GetNearestPassengerDoor | 0 | 1 | 0 | 0% | too few |
| PedAI.cpp | CPed::SetSeekBoatPosition | 0 | 1 | 0 | 0% | too few |
| PedAI.cpp | CPed::QuitEnteringCar | 1 | 0 | 0 | 100% | too few |
| PedAI.cpp | CPed::ClearObjective | 1 | 0 | 0 | 100% | too few |
| PedAI.cpp | CPed::ForceStoredObjective | 0 | 1 | 0 | 0% | too few |
| PedAI.cpp | CPed::LineUpPedWithTrain | 0 | 0 | 1 | 0% | too few |
| PedAI.cpp | CPed::PedAnimDoorCloseRollingCB | 1 | 0 | 0 | 100% | too few |
| PedAI.cpp | CPed::SeekBoatPosition | 1 | 0 | 0 | 100% | too few |
| PedAI.cpp | CPed::GetNextPointOnRoute | 0 | 0 | 1 | 0% | too few |
| Automobile.cpp | CAutomobile::ProcessControl | 36 | 24 | 13 | 60% | not ready |
| Automobile.cpp | CAutomobile::PreRender | 23 | 20 | 1 | 53% | not ready |
| Automobile.cpp | CAutomobile::HydraulicControl | 0 | 0 | 33 | 0% | too few |
| Automobile.cpp | CAutomobile::VehicleDamage | 15 | 6 | 2 | 71% | not ready |
| Automobile.cpp | CAutomobile::Render | 4 | 14 | 5 | 22% | not ready |
| Automobile.cpp | CAutomobile::SpawnFlyingComponent | 6 | 5 | 0 | 55% | not ready |
| Automobile.cpp | CAutomobile::ProcessBuoyancy | 1 | 0 | 9 | 100% | too few |
| Automobile.cpp | CAutomobile::TankControl | 4 | 2 | 2 | 67% | not ready |
| Automobile.cpp | CAutomobile::FireTruckControl | 1 | 2 | 4 | 33% | too few |
| Automobile.cpp | CAutomobile::BlowUpCar | 5 | 2 | 0 | 71% | not ready |
| Automobile.cpp | CAutomobile::ProcessAutoBusDoors | 0 | 0 | 4 | 0% | too few |
| Automobile.cpp | CAutomobile::CAutomobile | 3 | 0 | 1 | 100% | too few |
| Automobile.cpp | CPed::MakeTyresMuddySectorList | 1 | 3 | 0 | 25% | too few |
| Automobile.cpp | CAutomobile::ProcessControlInputs | 1 | 1 | 1 | 50% | too few |
| Automobile.cpp | CAutomobile::dmgDrawCarCollidingParticles | 3 | 0 | 0 | 100% | too few |
| Automobile.cpp | CAutomobile::Fix | 0 | 0 | 3 | 0% | too few |
| Automobile.cpp | CAutomobile::OpenDoor | 2 | 1 | 0 | 67% | too few |
| Automobile.cpp | CAutomobile::AddDamagedVehicleParticles | 2 | 1 | 0 | 67% | too few |
| Automobile.cpp | CAutomobile::HasCarStoppedBecauseOfLight | 2 | 1 | 0 | 67% | too few |
| Automobile.cpp | CAutomobile::PlaceOnRoadProperly | 0 | 0 | 2 | 0% | too few |
| Automobile.cpp | CAutomobile::BlowUpCarsInPath | 2 | 0 | 0 | 100% | too few |
| Automobile.cpp | CAutomobile::IsRoomForPedToLeaveCar | 1 | 1 | 0 | 50% | too few |
| Automobile.cpp | CAutomobile::ProcessEntityCollision | 1 | 1 | 0 | 50% | too few |
| Automobile.cpp | CAutomobile::BurstTyre | 0 | 0 | 2 | 0% | too few |
| Automobile.cpp | CAutomobile::AddWheelDirtAndWater | 0 | 0 | 2 | 0% | too few |
| Automobile.cpp | CAutomobile::ProcessOpenDoor | 0 | 0 | 2 | 0% | too few |
| Automobile.cpp | CAutomobile::SetBusDoorTimer | 0 | 0 | 2 | 0% | too few |
| Automobile.cpp | CAutomobile::RemoveBonnetInPedCollision | 0 | 0 | 1 | 0% | too few |
| Automobile.cpp | CAutomobile::SetupSuspensionLines | 1 | 0 | 0 | 100% | too few |
| Automobile.cpp | CAutomobile::SetDoorDamage | 0 | 1 | 0 | 0% | too few |
| Automobile.cpp | ProcessDoorCloseAnimation | 1 | 0 | 0 | 100% | too few |
| Automobile.cpp | ProcessDoorOpenCloseAnimation | 0 | 1 | 0 | 0% | too few |
| Automobile.cpp | CAutomobile::RcbanditCheck1CarWheels | 0 | 0 | 1 | 0% | too few |
| Automobile.cpp | CPed::DeadPedMakesTyresBloody | 0 | 1 | 0 | 0% | too few |
| Automobile.cpp | CAutomobile::SetupDamageAfterLoad | 0 | 0 | 1 | 0% | too few |
| Automobile.cpp | CAutomobile::RcbanditCheckHitWheels | 0 | 0 | 1 | 0% | too few |
| Automobile.cpp | CAutomobile::SetUpWheelColModel | 0 | 0 | 1 | 0% | too few |
| Automobile.cpp | CAutomobile::ReduceHornCounter | 1 | 0 | 0 | 100% | too few |
| Automobile.cpp | CAutomobile::ResetSuspension | 0 | 0 | 1 | 0% | too few |
| Automobile.cpp | CAutomobile::Load | 0 | 0 | 1 | 0% | too few |
| Automobile.cpp | CAutomobile::Save | 0 | 0 | 1 | 0% | too few |
| Automobile.cpp | CAutomobile::SetupModelNodes | 1 | 0 | 0 | 100% | too few |

## Operators

| Operator | Killed | Survived | No coverage | Covered score |
| --- | --- | --- | --- | --- |
| cxx_remove_void_call | 159 | 76 | 310 | 68% |
| cxx_eq_to_ne | 118 | 65 | 87 | 64% |
| cxx_add_to_sub | 84 | 24 | 88 | 78% |
| cxx_mul_to_div | 52 | 30 | 81 | 63% |
| cxx_lt_to_le | 16 | 63 | 45 | 20% |
| cxx_sub_to_add | 41 | 13 | 62 | 76% |
| cxx_lt_to_ge | 65 | 13 | 37 | 83% |
| cxx_gt_to_le | 54 | 11 | 45 | 83% |
| cxx_ne_to_eq | 44 | 24 | 34 | 65% |
| cxx_gt_to_ge | 17 | 44 | 39 | 28% |
| cxx_post_inc_to_post_dec | 31 | 6 | 15 | 84% |
| cxx_div_to_mul | 23 | 6 | 22 | 79% |
| cxx_le_to_gt | 16 | 6 | 8 | 73% |
| cxx_le_to_lt | 4 | 18 | 7 | 18% |
| cxx_rem_to_div | 10 | 0 | 15 | 100% |
| cxx_ge_to_lt | 14 | 4 | 6 | 78% |
| cxx_minus_to_noop | 9 | 6 | 7 | 60% |
| cxx_ge_to_gt | 4 | 9 | 8 | 31% |
| cxx_pre_inc_to_pre_dec | 1 | 1 | 3 | 50% |

## Survivors (first 60)

- src/control/CarCtrl.cpp:827 CCarCtrl::UpdateCarOnRails `*` -> `/` (cxx_mul_to_div)
- src/peds/Ped.cpp:3505 CPed::GetLocalDirection `<` -> `<=` (cxx_lt_to_le)
- src/peds/PedAI.cpp:2668 CPed::PedAnimGetInCB `==` -> `!=` (cxx_eq_to_ne)
- src/core/Frontend.cpp:5315 CMenuManager::ProcessButtonPresses `-` -> `+` (cxx_sub_to_add)
- src/peds/Ped.cpp:4023 CPed::SetDirectionToWalkAroundObject `==` -> `!=` (cxx_eq_to_ne)
- src/control/CarCtrl.cpp:1278 CCarCtrl::FindAngleToWeaveThroughTraffic `WeaveThroughObjectsSectorList(s->m_lists[ENTITYLIST_OBJECTS_` -> `((void)0)` (cxx_remove_void_call)
- src/core/Cam.cpp:3308 CCam::Process_BehindBoat `+` -> `-` (cxx_add_to_sub)
- src/peds/Ped.cpp:1647 CPed::ProcessBuoyancy `>` -> `>=` (cxx_gt_to_ge)
- src/control/CarCtrl.cpp:2191 CCarCtrl::SteerAICarWithPhysics_OnlyMission `==` -> `!=` (cxx_eq_to_ne)
- src/peds/PedAI.cpp:2031 CPed::CanSeeEntity `<` -> `<=` (cxx_lt_to_le)
- src/control/CarCtrl.cpp:1099 CCarCtrl::SlowCarDownForOtherCar `-` -> `+` (cxx_sub_to_add)
- src/peds/Ped.cpp:1858 CPed::ProcessControl `<=` -> `<` (cxx_le_to_lt)
- src/peds/Ped.cpp:7324 CPed::SetWaitState `==` -> `!=` (cxx_eq_to_ne)
- src/control/CarCtrl.cpp:915 CCarCtrl::ScanForPedDanger `SlowCarDownForPedsSectorList(s->m_lists[ENTITYLIST_PEDS_OVER` -> `((void)0)` (cxx_remove_void_call)
- src/core/Cam.cpp:3618 CCam::Process_FlyBy `FindSplinePathPositionFloat(&UpAngle, TheCamera.m_arrPathArr` -> `((void)0)` (cxx_remove_void_call)
- src/peds/PedAI.cpp:4280 CPed::SetAnimOffsetForEnterOrExitVehicle `>` -> `>=` (cxx_gt_to_ge)
- src/peds/Ped.cpp:2566 CPed::ProcessControl `+` -> `-` (cxx_add_to_sub)
- src/control/CarCtrl.cpp:1838 CCarCtrl::PickNextNodeToChaseCar `+` -> `-` (cxx_add_to_sub)
- src/peds/Ped.cpp:7182 CPed::LookForInterestingNodes `>=` -> `>` (cxx_ge_to_gt)
- src/vehicles/Automobile.cpp:588 CAutomobile::ProcessControl `ProcessBuoyancy()` -> `((void)0)` (cxx_remove_void_call)
- src/control/CarCtrl.cpp:1021 CCarCtrl::SlowCarDownForPedsSectorList `<` -> `<=` (cxx_lt_to_le)
- src/peds/Ped.cpp:2461 CPed::ProcessControl `<=` -> `>` (cxx_le_to_gt)
- src/control/CarCtrl.cpp:2292 CCarCtrl::SteerAICarWithPhysicsFollowPath `>` -> `>=` (cxx_gt_to_ge)
- src/peds/Ped.cpp:2410 CPed::ProcessControl `==` -> `!=` (cxx_eq_to_ne)
- src/peds/PedAI.cpp:3518 CPed::SetEnterCar_AllClear `==` -> `!=` (cxx_eq_to_ne)
- src/core/Frontend.cpp:5716 CMenuManager::SwitchMenuOnAndOff `SaveINIControllerSettings()` -> `((void)0)` (cxx_remove_void_call)
- src/audio/AudioLogic.cpp:975 cAudioManager::ProcessRainOnVehicle `>` -> `<=` (cxx_gt_to_le)
- src/peds/PedAI.cpp:206 CPed::SetObjective `==` -> `!=` (cxx_eq_to_ne)
- src/vehicles/Automobile.cpp:1366 CAutomobile::PreRender `>` -> `>=` (cxx_gt_to_ge)
- src/vehicles/Automobile.cpp:1140 CAutomobile::ProcessControl `==` -> `!=` (cxx_eq_to_ne)
- src/control/CarCtrl.cpp:927 CCarCtrl::SlowCarOnRailsDownForTrafficAndLights `CCarAI::CarHasReasonToStop(pVehicle)` -> `((void)0)` (cxx_remove_void_call)
- src/vehicles/Automobile.cpp:2103 CAutomobile::Render `mat.Translate(pos)` -> `((void)0)` (cxx_remove_void_call)
- src/peds/Ped.cpp:5335 CPed::SetAttackTimer `>` -> `>=` (cxx_gt_to_ge)
- src/vehicles/Automobile.cpp:1902 CAutomobile::PreRender `+` -> `-` (cxx_add_to_sub)
- src/control/CarCtrl.cpp:2519 CCarCtrl::RegisterVehicleOfInterest `<` -> `<=` (cxx_lt_to_le)
- src/core/Frontend.cpp:5789 CMenuManager::UnloadTextures `!=` -> `==` (cxx_ne_to_eq)
- src/peds/PedAI.cpp:1377 CPed::ProcessObjective `<` -> `<=` (cxx_lt_to_le)
- src/control/CarCtrl.cpp:1102 CCarCtrl::SlowCarDownForOtherCar `!=` -> `==` (cxx_ne_to_eq)
- src/peds/Ped.cpp:7136 CPed::LookForInterestingNodes `<=` -> `<` (cxx_le_to_lt)
- src/control/CarCtrl.cpp:2639 CCarCtrl::FindLinksToGoWithTheseNodes `<` -> `<=` (cxx_lt_to_le)
- src/vehicles/Automobile.cpp:1984 CAutomobile::Render `mat.SetRotateX(m_aWheelRotation[CARWHEEL_REAR_RIGHT])` -> `((void)0)` (cxx_remove_void_call)
- src/core/Cam.cpp:594 CCam::ProcessSpecialHeightRoutines `==` -> `!=` (cxx_eq_to_ne)
- src/audio/AudioLogic.cpp:351 cAudioManager::PreTerminateGameSpecificShutdown `DestroyEntity(m_nCollisionEntity)` -> `((void)0)` (cxx_remove_void_call)
- src/control/CarCtrl.cpp:1293 CCarCtrl::FindAngleToWeaveThroughTraffic `<` -> `<=` (cxx_lt_to_le)
- src/peds/Ped.cpp:752 CPed::ScanForThreats `<` -> `<=` (cxx_lt_to_le)
- src/peds/Ped.cpp:1513 CPed::UpdatePosition `*` -> `/` (cxx_mul_to_div)
- src/peds/PedAI.cpp:3523 CPed::SetEnterCar_AllClear `m_pMyVehicle->RegisterReference((CEntity**) &m_pMyVehicle)` -> `((void)0)` (cxx_remove_void_call)
- src/core/Frontend.cpp:5307 CMenuManager::ProcessButtonPresses `<` -> `>=` (cxx_lt_to_ge)
- src/core/Cam.cpp:2181 CCam::Cam_On_A_String_Unobscured `<` -> `<=` (cxx_lt_to_le)
- src/peds/Ped.cpp:7324 CPed::SetWaitState `==` -> `!=` (cxx_eq_to_ne)
- src/audio/AudioLogic.cpp:2831 cAudioManager::ProcessHelicopter `<` -> `<=` (cxx_lt_to_le)
- src/control/CarCtrl.cpp:322 CCarCtrl::GenerateOneRandomCar `>` -> `>=` (cxx_gt_to_ge)
- src/peds/Ped.cpp:4645 CPed::PedSetInCarCB `==` -> `!=` (cxx_eq_to_ne)
- src/core/Cam.cpp:408 CCam::ProcessSpecialHeightRoutines `<` -> `>=` (cxx_lt_to_ge)
- src/audio/AudioLogic.cpp:2712 cAudioManager::ProcessBoatEngine `/` -> `*` (cxx_div_to_mul)
- src/audio/AudioLogic.cpp:418 cAudioManager::ProcessReverb `++` -> `--` (cxx_post_inc_to_post_dec)
- src/control/CarCtrl.cpp:988 CCarCtrl::SlowCarDownForPedsSectorList `+` -> `-` (cxx_add_to_sub)
- src/core/Cam.cpp:2384 CCam::Process_TopDownPed `<=` -> `<` (cxx_le_to_lt)
- src/core/Frontend.cpp:452 CMenuManager::ThingsToDoBeforeGoingBack `==` -> `!=` (cxx_eq_to_ne)
- src/control/CarCtrl.cpp:1914 CCarCtrl::PickNextNodeToFollowPath `+` -> `-` (cxx_add_to_sub)
