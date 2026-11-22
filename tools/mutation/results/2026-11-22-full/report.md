# Mutation results (Mull profile: cxx_default + cxx_remove_void_call)

| File | Killed | Survived | No coverage | Compile errors | Score | Covered score |
| --- | --- | --- | --- | --- | --- | --- |
| src/audio/AudioLogic.cpp | 710 | 257 | 895 | 0 | 38.1% | 73.4% |
| src/control/CarCtrl.cpp | 734 | 332 | 120 | 4 | 61.9% | 68.9% |
| src/core/Cam.cpp | 757 | 402 | 811 | 0 | 38.4% | 65.3% |
| src/core/Frontend.cpp | 158 | 172 | 1181 | 0 | 10.5% | 47.9% |
| src/peds/Ped.cpp | 1145 | 643 | 524 | 0 | 49.5% | 64.0% |
| src/peds/PedAI.cpp | 464 | 262 | 711 | 0 | 32.3% | 63.9% |
| src/vehicles/Automobile.cpp | 881 | 517 | 670 | 0 | 42.6% | 63.0% |
| **all** | 4849 | 2585 | 4912 | 4 | **39.3%** | **65.2%** |

## Functions (covered score; ImageMagick gate: ready >= 90%, careful 75-90%, not ready < 75%)

| File | Function | Killed | Survived | No coverage | Covered score | Verdict |
| --- | --- | --- | --- | --- | --- | --- |
| AudioLogic.cpp | cAudioManager::ProcessPlayersVehicleEngine | 76 | 28 | 27 | 73% | not ready |
| AudioLogic.cpp | cAudioManager::ProcessPedOneShots | 60 | 3 | 37 | 95% | ready |
| AudioLogic.cpp | cAudioManager::ProcessVehicleOneShots | 46 | 8 | 29 | 85% | careful |
| AudioLogic.cpp | cAudioManager::ProcessVehicleEngine | 59 | 10 | 0 | 86% | careful |
| AudioLogic.cpp | cAudioManager::ProcessBoatEngine | 47 | 7 | 4 | 87% | careful |
| AudioLogic.cpp | cAudioManager::ProcessOneShotScriptObject | 14 | 2 | 21 | 88% | careful |
| AudioLogic.cpp | cAudioManager::ProcessCesna | 26 | 1 | 7 | 96% | ready |
| AudioLogic.cpp | cAudioManager::ProcessGarages | 1 | 6 | 25 | 14% | not ready |
| AudioLogic.cpp | cAudioManager::ProcessMissionAudio | 3 | 6 | 19 | 33% | not ready |
| AudioLogic.cpp | cAudioManager::ProcessWeather | 17 | 6 | 0 | 74% | not ready |
| AudioLogic.cpp | cAudioManager::ProcessVehicleSkidding | 18 | 3 | 2 | 86% | careful |
| AudioLogic.cpp | cAudioManager::ProcessJumbo | 5 | 6 | 12 | 45% | not ready |
| AudioLogic.cpp | cAudioManager::PostInitialiseGameSpecificSetup | 3 | 19 | 0 | 14% | not ready |
| AudioLogic.cpp | cAudioManager::ProcessVehicle | 10 | 9 | 2 | 53% | not ready |
| AudioLogic.cpp | cAudioManager::ProcessModelCarEngine | 0 | 0 | 21 | 0% | too few |
| AudioLogic.cpp | cAudioManager::PreTerminateGameSpecificShutdown | 0 | 21 | 0 | 0% | not ready |
| AudioLogic.cpp | cAudioManager::SetupPedComments | 6 | 0 | 15 | 100% | ready |
| AudioLogic.cpp | cPedComments::Process | 12 | 8 | 0 | 60% | not ready |
| AudioLogic.cpp | cAudioManager::ProcessFrontEnd | 11 | 4 | 5 | 73% | not ready |
| AudioLogic.cpp | cAudioManager::ProcessReverseGear | 17 | 0 | 0 | 100% | ready |
| AudioLogic.cpp | cAudioManager::ProcessPornCinema | 0 | 0 | 17 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessVehicleRoadNoise | 14 | 0 | 3 | 100% | ready |
| AudioLogic.cpp | cPedComments::Add | 12 | 2 | 3 | 86% | careful |
| AudioLogic.cpp | cAudioManager::ProcessHelicopter | 9 | 4 | 4 | 69% | not ready |
| AudioLogic.cpp | cAudioManager::ProcessVehicleDoors | 15 | 1 | 0 | 94% | ready |
| AudioLogic.cpp | cAudioManager::ProcessPoliceCellBeatingScriptObject | 0 | 0 | 16 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessRainOnVehicle | 13 | 3 | 0 | 81% | careful |
| AudioLogic.cpp | cAudioManager::ProcessHomeScriptObject | 1 | 3 | 11 | 25% | too few |
| AudioLogic.cpp | cAudioManager::ProcessCinemaScriptObject | 0 | 0 | 15 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessShopScriptObject | 1 | 1 | 13 | 50% | too few |
| AudioLogic.cpp | cAudioManager::ProcessLoopingScriptObject | 4 | 7 | 4 | 36% | not ready |
| AudioLogic.cpp | cAudioManager::ProcessAirBrakes | 8 | 6 | 0 | 57% | not ready |
| AudioLogic.cpp | cAudioManager::ProcessWetRoadNoise | 10 | 4 | 0 | 71% | not ready |
| AudioLogic.cpp | cAudioManager::ProcessTrainNoise | 12 | 2 | 0 | 86% | careful |
| AudioLogic.cpp | cAudioManager::ProcessBridgeOneShots | 0 | 8 | 5 | 0% | not ready |
| AudioLogic.cpp | cAudioManager::SetupJumboTaxiSound | 0 | 0 | 13 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetVehicleDriveWheelSkidValue | 9 | 4 | 0 | 69% | not ready |
| AudioLogic.cpp | cAudioManager::ProcessExplosions | 8 | 1 | 4 | 89% | careful |
| AudioLogic.cpp | cAudioManager::ProcessDocksScriptObject | 1 | 3 | 9 | 25% | too few |
| AudioLogic.cpp | cAudioManager::ProcessSawMillScriptObject | 1 | 1 | 11 | 50% | too few |
| AudioLogic.cpp | cAudioManager::GetHoodTalkSfx | 0 | 0 | 12 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessFires | 0 | 3 | 9 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessAirportScriptObject | 1 | 3 | 8 | 25% | too few |
| AudioLogic.cpp | cAudioManager::ProcessEntity | 4 | 7 | 1 | 36% | not ready |
| AudioLogic.cpp | cAudioManager::GetDiabloTalkSfx | 0 | 0 | 12 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetLittleItalyMaleTalkSfx | 0 | 0 | 11 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessVehicleHorn | 10 | 1 | 0 | 91% | ready |
| AudioLogic.cpp | cAudioManager::GetMafiaTalkSfx | 0 | 0 | 11 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetColumbianTalkSfx | 0 | 0 | 11 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessBoatMovingOverWater | 9 | 2 | 0 | 82% | careful |
| AudioLogic.cpp | cAudioManager::ProcessJumboLanding | 0 | 0 | 10 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetWhiteFemaleProstituteTalkSfx | 0 | 0 | 10 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetYakuzaTalkSfx | 0 | 0 | 10 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetBusinessMaleYoungTalkSfx | 0 | 0 | 10 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetYardieTalkSfx | 0 | 0 | 10 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetWhiteBusinessFemaleTalkSfx | 0 | 0 | 10 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetBlackProjectMaleTalkSfx | 5 | 0 | 5 | 100% | ready |
| AudioLogic.cpp | cAudioManager::GetBlackFemaleProstituteTalkSfx | 0 | 0 | 10 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetShopperFemaleTalkSfx | 0 | 0 | 10 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessEngineDamage | 7 | 3 | 0 | 70% | not ready |
| AudioLogic.cpp | cAudioManager::ProcessCrane | 0 | 2 | 7 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetFBITalkSfx | 0 | 0 | 9 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetSwatTalkSfx | 0 | 0 | 9 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessVehicleReverseWarning | 7 | 2 | 0 | 78% | careful |
| AudioLogic.cpp | cAudioManager::GetCopTalkSfx | 9 | 0 | 0 | 100% | ready |
| AudioLogic.cpp | cAudioManager::ProcessJumboAccel | 0 | 0 | 9 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessVehicleSirenOrAlarm | 8 | 1 | 0 | 89% | careful |
| AudioLogic.cpp | cAudioManager::GetMedicTalkSfx | 0 | 0 | 9 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetFanFemaleTalkSfx | 0 | 0 | 8 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetBlackBusinessFemaleTalkSfx | 0 | 0 | 8 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetFemaleNo3TalkSfx | 3 | 0 | 5 | 100% | too few |
| AudioLogic.cpp | cAudioManager::GetBusinessMaleOldTalkSfx | 0 | 0 | 8 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetStewardFemaleTalkSfx | 0 | 0 | 8 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetNormalMaleTalkSfx | 0 | 0 | 8 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ResetAudioLogicTimers | 4 | 4 | 0 | 50% | not ready |
| AudioLogic.cpp | cAudioManager::ProcessLaunderetteScriptObject | 1 | 1 | 6 | 50% | too few |
| AudioLogic.cpp | cAudioManager::GetArmyTalkSfx | 0 | 0 | 8 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetTriadTalkSfx | 0 | 0 | 8 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessProjectiles | 3 | 3 | 2 | 50% | not ready |
| AudioLogic.cpp | cAudioManager::GetBlackCasualFemaleTalkSfx | 2 | 0 | 6 | 100% | too few |
| AudioLogic.cpp | cAudioManager::SetupJumboEngineSound | 1 | 1 | 5 | 50% | too few |
| AudioLogic.cpp | cAudioManager::GetSupermodelMaleTalkSfx | 0 | 0 | 7 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessPedHeadphones | 5 | 2 | 0 | 71% | not ready |
| AudioLogic.cpp | cAudioManager::GetWhiteFatFemaleTalkSfx | 0 | 0 | 7 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetCasualMaleOldTalkSfx | 4 | 0 | 3 | 100% | too few |
| AudioLogic.cpp | cAudioManager::GetFanMaleTalkSfx | 0 | 0 | 7 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetPhrase | 7 | 0 | 0 | 100% | ready |
| AudioLogic.cpp | cAudioManager::GetStudentMaleTalkSfx | 0 | 0 | 7 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetStudentFemaleTalkSfx | 0 | 0 | 7 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetBlackConstructionWorkerTalkSfx | 0 | 0 | 7 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetBlackFatFemaleTalkSfx | 4 | 0 | 3 | 100% | too few |
| AudioLogic.cpp | cAudioManager::GetPimpTalkSfx | 0 | 0 | 7 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetChinatownMaleYoungTalkSfx | 0 | 0 | 7 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetBlackProjectFemaleOldTalkSfx | 0 | 0 | 7 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetScumMaleTalkSfx | 0 | 0 | 7 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetChinatownMaleOldTalkSfx | 0 | 0 | 7 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessJumboTakeOff | 0 | 0 | 7 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetWhiteCasualFemaleTalkSfx | 4 | 0 | 3 | 100% | too few |
| AudioLogic.cpp | cAudioManager::SetupJumboRumbleSound | 0 | 0 | 6 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessSpecial | 1 | 5 | 0 | 17% | not ready |
| AudioLogic.cpp | cAudioManager::GetWhiteConstructionWorkerTalkSfx | 0 | 0 | 6 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetLittleItalyFemaleOldTalkSfx | 0 | 0 | 6 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetDistanceSquared | 6 | 0 | 0 | 100% | ready |
| AudioLogic.cpp | cAudioManager::GetBlackDockerMaleTalkSfx | 0 | 0 | 6 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetWhiteDockerMaleTalkSfx | 0 | 0 | 6 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetSupermodelFemaleTalkSfx | 0 | 0 | 6 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetScumFemaleTalkSfx | 0 | 0 | 6 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetWhiteFatMaleTalkSfx | 1 | 0 | 5 | 100% | too few |
| AudioLogic.cpp | cAudioManager::GetBlackProjectFemaleYoungTalkSfx | 0 | 0 | 6 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetAsianTaxiDriverTalkSfx | 6 | 0 | 0 | 100% | ready |
| AudioLogic.cpp | cAudioManager::ProcessWaterCannon | 3 | 3 | 0 | 50% | not ready |
| AudioLogic.cpp | cAudioManager::GetBlackWorkerMaleTalkSfx | 0 | 0 | 6 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetWhiteWorkerMaleTalkSfx | 0 | 0 | 6 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetLittleItalyFemaleYoungTalkSfx | 0 | 0 | 6 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetBlackFatMaleTalkSfx | 4 | 0 | 2 | 100% | too few |
| AudioLogic.cpp | cAudioManager::GetChinatownFemaleYoungTalkSfx | 0 | 0 | 6 | 0% | too few |
| AudioLogic.cpp | cAudioManager::HasAirBrakes | 5 | 0 | 0 | 100% | ready |
| AudioLogic.cpp | cAudioManager::ProcessBridgeMotor | 0 | 0 | 5 | 0% | too few |
| AudioLogic.cpp | cAudioManager::SetupJumboWhineSound | 0 | 0 | 5 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetMistyTalkSfx | 0 | 0 | 5 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessWorkShopScriptObject | 0 | 0 | 5 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetChinatownFemaleOldTalkSfx | 0 | 0 | 5 | 0% | too few |
| AudioLogic.cpp | cAudioManager::UsesReverseWarning | 5 | 0 | 0 | 100% | ready |
| AudioLogic.cpp | cAudioManager::ProcessCarBombTick | 1 | 0 | 4 | 100% | too few |
| AudioLogic.cpp | cAudioManager::GetHospitalMaleTalkSfx | 0 | 0 | 5 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetBlackCriminalTalkSfx | 0 | 0 | 5 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessBridgeWarning | 0 | 0 | 5 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessBridge | 1 | 2 | 2 | 33% | too few |
| AudioLogic.cpp | cAudioManager::GetStewardMaleTalkSfx | 0 | 0 | 5 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetWhiteCriminalTalkSfx | 0 | 0 | 5 | 0% | too few |
| AudioLogic.cpp | cAudioManager::SetupJumboFlySound | 3 | 2 | 0 | 60% | not ready |
| AudioLogic.cpp | DoJumboVolOffset | 0 | 3 | 1 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetGenericFemaleTalkSfx | 3 | 0 | 1 | 100% | too few |
| AudioLogic.cpp | cAudioManager::GetSalvatoreTalkSfx | 0 | 0 | 4 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessFireHydrant | 0 | 0 | 4 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetGenericMaleTalkSfx | 3 | 0 | 1 | 100% | too few |
| AudioLogic.cpp | cAudioManager::ProcessReverb | 0 | 4 | 0 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetEightBallTalkSfx | 0 | 0 | 4 | 0% | too few |
| AudioLogic.cpp | cAudioManager::PreloadMissionAudio | 1 | 2 | 0 | 33% | too few |
| AudioLogic.cpp | cAudioManager::GetSecurityGuardTalkSfx | 0 | 0 | 3 | 0% | too few |
| AudioLogic.cpp | cAudioManager::AddPlayerCarSample | 2 | 1 | 0 | 67% | too few |
| AudioLogic.cpp | cAudioManager::PlayLoadedMissionAudio | 3 | 0 | 0 | 100% | too few |
| AudioLogic.cpp | cAudioManager::GetJumboTaxiFreq | 0 | 0 | 3 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetHospitalFemaleTalkSfx | 0 | 0 | 3 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetPlayerTalkSfx | 3 | 0 | 0 | 100% | too few |
| AudioLogic.cpp | cAudioManager::ProcessScriptObject | 3 | 0 | 0 | 100% | too few |
| AudioLogic.cpp | cAudioManager::IsMissionAudioSampleFinished | 1 | 0 | 2 | 100% | too few |
| AudioLogic.cpp | cAudioManager::ProcessPed | 3 | 0 | 0 | 100% | too few |
| AudioLogic.cpp | cAudioManager::ProcessPlane | 0 | 2 | 0 | 0% | too few |
| AudioLogic.cpp | cAudioManager::ProcessPhysical | 2 | 0 | 0 | 100% | too few |
| AudioLogic.cpp | cAudioManager::UpdateGasPedalAudio | 1 | 1 | 0 | 50% | too few |
| AudioLogic.cpp | cAudioManager::ProcessJumboDecel | 0 | 0 | 2 | 0% | too few |
| AudioLogic.cpp | cAudioManager::GetVehicleNonDriveWheelSkidValue | 1 | 0 | 0 | 100% | too few |
| AudioLogic.cpp | cAudioManager::GetBomberTalkSfx | 0 | 0 | 1 | 0% | too few |
| AudioLogic.cpp | FindMissionAudioSfx | 1 | 0 | 0 | 100% | too few |
| AudioLogic.cpp | cAudioManager::GetChunkyTalkSfx | 0 | 0 | 1 | 0% | too few |
| CarCtrl.cpp | CCarCtrl::GenerateOneRandomCar | 133 | 46 | 0 | 74% | not ready |
| CarCtrl.cpp | CCarCtrl::TestCollisionBetween2MovingRects | 94 | 18 | 0 | 84% | careful |
| CarCtrl.cpp | CCarCtrl::SteerAICarWithPhysicsFollowPath | 54 | 15 | 1 | 78% | careful |
| CarCtrl.cpp | CCarCtrl::PickNextNodeRandomly | 50 | 18 | 0 | 74% | not ready |
| CarCtrl.cpp | CCarCtrl::SlowCarDownForPedsSectorList | 37 | 24 | 5 | 61% | not ready |
| CarCtrl.cpp | CCarCtrl::PickNextNodeToChaseCar | 17 | 39 | 5 | 30% | not ready |
| CarCtrl.cpp | CCarCtrl::ChooseModel | 33 | 0 | 9 | 100% | ready |
| CarCtrl.cpp | CCarCtrl::PickNextNodeToFollowPath | 11 | 26 | 0 | 30% | not ready |
| CarCtrl.cpp | CCarCtrl::GenerateEmergencyServicesCar | 0 | 16 | 15 | 0% | not ready |
| CarCtrl.cpp | CCarCtrl::SlowCarDownForOtherCar | 13 | 16 | 2 | 45% | not ready |
| CarCtrl.cpp | CCarCtrl::UpdateCarOnRails | 23 | 5 | 0 | 82% | careful |
| CarCtrl.cpp | CCarCtrl::SteerAICarWithPhysics | 15 | 1 | 12 | 94% | ready |
| CarCtrl.cpp | CCarCtrl::FindAngleToWeaveThroughTraffic | 21 | 5 | 0 | 81% | careful |
| CarCtrl.cpp | CCarCtrl::WeaveForOtherCar | 18 | 7 | 0 | 72% | not ready |
| CarCtrl.cpp | CCarCtrl::GenerateOneEmergencyServicesCar | 0 | 0 | 21 | 0% | too few |
| CarCtrl.cpp | CCarCtrl::PossiblyRemoveVehicle | 12 | 8 | 1 | 60% | not ready |
| CarCtrl.cpp | CCarCtrl::DragCarToPoint | 16 | 4 | 0 | 80% | careful |
| CarCtrl.cpp | CCarCtrl::SteerAICarWithPhysics_OnlyMission | 10 | 5 | 4 | 67% | not ready |
| CarCtrl.cpp | CCarCtrl::WeaveForObject | 15 | 2 | 0 | 88% | careful |
| CarCtrl.cpp | CCarCtrl::FindMaximumSpeedForThisCarInTraffic | 13 | 3 | 0 | 81% | careful |
| CarCtrl.cpp | CCarCtrl::FindLinksToGoWithTheseNodes | 12 | 3 | 0 | 80% | careful |
| CarCtrl.cpp | CCarCtrl::SteerAIBoatWithPhysicsHeadingForTarget | 0 | 0 | 14 | 0% | too few |
| CarCtrl.cpp | CCarCtrl::SlowCarDownForCarsSectorList | 9 | 5 | 0 | 64% | not ready |
| CarCtrl.cpp | CCarCtrl::SteerAICarWithPhysicsHeadingForTarget | 12 | 2 | 0 | 86% | careful |
| CarCtrl.cpp | CCarCtrl::JoinCarWithRoadSystem | 9 | 4 | 0 | 69% | not ready |
| CarCtrl.cpp | CCarCtrl::FindPathDirection | 11 | 2 | 0 | 85% | careful |
| CarCtrl.cpp | CCarCtrl::WeaveThroughObjectsSectorList | 8 | 5 | 0 | 62% | not ready |
| CarCtrl.cpp | CCarCtrl::WeaveThroughCarsSectorList | 9 | 4 | 0 | 69% | not ready |
| CarCtrl.cpp | CCarCtrl::WeaveThroughPedsSectorList | 9 | 4 | 0 | 69% | not ready |
| CarCtrl.cpp | CCarCtrl::RegisterVehicleOfInterest | 0 | 7 | 5 | 0% | not ready |
| CarCtrl.cpp | CCarCtrl::WeaveForPed | 10 | 2 | 0 | 83% | careful |
| CarCtrl.cpp | CCarCtrl::GenerateRandomCars | 8 | 3 | 0 | 73% | not ready |
| CarCtrl.cpp | CCarCtrl::SlowCarOnRailsDownForTrafficAndLights | 9 | 2 | 0 | 82% | careful |
| CarCtrl.cpp | CCarCtrl::ScanForPedDanger | 6 | 3 | 0 | 67% | not ready |
| CarCtrl.cpp | CCarCtrl::Init | 3 | 6 | 0 | 33% | not ready |
| CarCtrl.cpp | CCarCtrl::JoinCarWithRoadSystemGotoCoors | 7 | 0 | 0 | 100% | ready |
| CarCtrl.cpp | CCarCtrl::MapCouldMoveInThisArea | 0 | 4 | 4 | 0% | too few |
| CarCtrl.cpp | CCarCtrl::SteerAICarWithPhysicsTryingToBlockTarget_Stop | 3 | 4 | 1 | 43% | not ready |
| CarCtrl.cpp | CCarCtrl::FindSpeedMultiplier | 7 | 1 | 0 | 88% | careful |
| CarCtrl.cpp | CCarCtrl::ReInit | 0 | 0 | 6 | 0% | too few |
| CarCtrl.cpp | CCarCtrl::UpdateCarCount | 2 | 2 | 1 | 50% | too few |
| CarCtrl.cpp | CCarCtrl::CountCarsOfType | 0 | 0 | 5 | 0% | too few |
| CarCtrl.cpp | CCarCtrl::RemoveDistantCars | 3 | 1 | 1 | 75% | too few |
| CarCtrl.cpp | CCarCtrl::ChooseGangCarModel | 0 | 0 | 4 | 0% | too few |
| CarCtrl.cpp | CCarCtrl::IsThisVehicleInteresting | 3 | 1 | 0 | 75% | too few |
| CarCtrl.cpp | CCarCtrl::RemoveFromInterestingVehicleList | 1 | 3 | 0 | 25% | too few |
| CarCtrl.cpp | CCarCtrl::ChooseCarModel | 2 | 1 | 0 | 67% | too few |
| CarCtrl.cpp | CCarCtrl::ClearInterestingVehicleList | 1 | 2 | 0 | 33% | too few |
| CarCtrl.cpp | CCarCtrl::SteerAIBoatWithPhysics | 0 | 0 | 3 | 0% | too few |
| CarCtrl.cpp | CCarCtrl::PickNextNodeAccordingStrategy | 1 | 0 | 1 | 100% | too few |
| CarCtrl.cpp | CCarCtrl::ThisRoadObjectCouldMove | 0 | 2 | 0 | 0% | too few |
| CarCtrl.cpp | CCarCtrl::SteerAICarWithPhysicsTryingToBlockTarget | 2 | 0 | 0 | 100% | too few |
| CarCtrl.cpp | CCarCtrl::ChoosePoliceCarModel | 0 | 1 | 0 | 0% | too few |
| CarCtrl.cpp | CCarCtrl::FindMaxSteerAngle | 1 | 0 | 0 | 100% | too few |
| CarCtrl.cpp | CCarCtrl::AddToCarArray | 1 | 0 | 0 | 100% | too few |
| Cam.cpp | CCam::Process_FollowCar_SA | 172 | 79 | 53 | 69% | not ready |
| Cam.cpp | CCam::Process_FollowPed | 85 | 33 | 37 | 72% | not ready |
| Cam.cpp | FindSplinePathPositionVector | 67 | 9 | 13 | 88% | careful |
| Cam.cpp | CCam::Process | 25 | 25 | 26 | 50% | not ready |
| Cam.cpp | CCam::Process_FollowPedWithMouse | 46 | 27 | 1 | 63% | not ready |
| Cam.cpp | CCam::WorkOutCamHeight | 41 | 21 | 10 | 66% | not ready |
| Cam.cpp | CCam::ProcessSpecialHeightRoutines | 3 | 61 | 4 | 5% | not ready |
| Cam.cpp | CCam::Process_BehindBoat | 37 | 24 | 6 | 61% | not ready |
| Cam.cpp | CCam::Process_Sniper | 13 | 27 | 25 | 32% | not ready |
| Cam.cpp | CCam::Process_FollowPed_Rotation | 0 | 0 | 62 | 0% | too few |
| Cam.cpp | CCam::Process_1rstPersonPedOnPC | 0 | 0 | 51 | 0% | too few |
| Cam.cpp | CCam::Process_FlyBy | 12 | 15 | 18 | 44% | not ready |
| Cam.cpp | CCam::Process_Rocket | 12 | 16 | 16 | 43% | not ready |
| Cam.cpp | CCam::Process_M16_1stPerson | 0 | 0 | 44 | 0% | too few |
| Cam.cpp | FindSplinePathPositionFloat | 25 | 5 | 13 | 83% | careful |
| Cam.cpp | CCam::Process_TopDownPed | 30 | 11 | 2 | 73% | not ready |
| Cam.cpp | CCam::Process_1stPerson | 8 | 0 | 34 | 100% | ready |
| Cam.cpp | CCam::Process_Syphon | 0 | 0 | 40 | 0% | too few |
| Cam.cpp | CCam::Process_Debug | 0 | 0 | 35 | 0% | too few |
| Cam.cpp | CCam::Process_ReactionCam | 0 | 0 | 33 | 0% | too few |
| Cam.cpp | CCam::Process_FollowPed_WithBinding | 0 | 0 | 33 | 0% | too few |
| Cam.cpp | CCam::Process_Chris_With_Binding_PlusRotation | 0 | 0 | 31 | 0% | too few |
| Cam.cpp | CCam::Process_TopDown | 0 | 0 | 26 | 0% | too few |
| Cam.cpp | CCam::Process_BehindCar | 0 | 0 | 26 | 0% | too few |
| Cam.cpp | CCam::Process_Editor | 0 | 0 | 26 | 0% | too few |
| Cam.cpp | CCam::WorkOutCamHeightWeeCar | 0 | 0 | 25 | 0% | too few |
| Cam.cpp | CCam::ProcessPedsDeadBaby | 16 | 9 | 0 | 64% | not ready |
| Cam.cpp | CCam::Process_Syphon_Crim_In_Front | 0 | 0 | 24 | 0% | too few |
| Cam.cpp | CCam::LookBehind | 8 | 4 | 12 | 67% | not ready |
| Cam.cpp | CCam::Cam_On_A_String_Unobscured | 18 | 3 | 1 | 86% | careful |
| Cam.cpp | CCam::Process_Fight_Cam | 17 | 5 | 0 | 77% | careful |
| Cam.cpp | CCam::ProcessArrestCamTwo | 18 | 1 | 0 | 95% | ready |
| Cam.cpp | CCam::FixCamIfObscured | 16 | 1 | 1 | 94% | ready |
| Cam.cpp | CCam::RotCamIfInFrontCar | 13 | 2 | 0 | 87% | careful |
| Cam.cpp | CCam::LookRight | 0 | 0 | 15 | 0% | too few |
| Cam.cpp | CCam::Process_ModelView | 0 | 0 | 15 | 0% | too few |
| Cam.cpp | CCam::LookLeft | 9 | 2 | 4 | 82% | careful |
| Cam.cpp | CCam::DoAverageOnVector | 12 | 1 | 0 | 92% | ready |
| Cam.cpp | CCam::GetPedBetaAngleForClearView | 9 | 4 | 0 | 69% | not ready |
| Cam.cpp | WellBufferMe | 10 | 3 | 0 | 77% | careful |
| Cam.cpp | CCam::ClipIfPedInFrontOfPlayer | 2 | 4 | 4 | 33% | not ready |
| Cam.cpp | CCam::Process_Cam_On_A_String | 8 | 0 | 0 | 100% | ready |
| Cam.cpp | CCam::AvoidWallsTopDownPed | 6 | 2 | 0 | 75% | careful |
| Cam.cpp | CCam::Process_Bill | 0 | 0 | 6 | 0% | too few |
| Cam.cpp | CCam::Process_Player_Fallen_Water | 6 | 0 | 0 | 100% | ready |
| Cam.cpp | CCam::FixCamWhenObscuredByVehicle | 5 | 1 | 0 | 83% | careful |
| Cam.cpp | CCam::Process_Fixed | 2 | 2 | 2 | 50% | too few |
| Cam.cpp | CCam::Process_Circle | 0 | 0 | 6 | 0% | too few |
| Cam.cpp | CCam::KeepTrackOfTheSpeed | 1 | 4 | 0 | 20% | not ready |
| Cam.cpp | CCam::ProcessArrestCamOne | 0 | 0 | 5 | 0% | too few |
| Cam.cpp | CCam::Process_WheelCam | 0 | 0 | 5 | 0% | too few |
| Cam.cpp | CCam::GetVectorsReadyForRW | 4 | 0 | 0 | 100% | too few |
| Cam.cpp | CCam::Process_Blood_On_The_Tracks | 0 | 0 | 4 | 0% | too few |
| Cam.cpp | CCam::Process_SpecialFixedForSyphon | 0 | 0 | 4 | 0% | too few |
| Cam.cpp | CCam::Process_Cam_Running_Side_Train | 0 | 0 | 4 | 0% | too few |
| Cam.cpp | CCam::Using3rdPersonMouseCam | 1 | 0 | 3 | 100% | too few |
| Cam.cpp | CCam::Process_Cam_On_Train_Roof | 0 | 0 | 3 | 0% | too few |
| Cam.cpp | CCam::PrintMode | 0 | 1 | 1 | 0% | too few |
| Cam.cpp | CCam::Process_Im_The_Passenger_Woo_Woo | 0 | 0 | 2 | 0% | too few |
| Frontend.cpp | CMenuManager::ProcessButtonPresses | 60 | 40 | 178 | 60% | not ready |
| Frontend.cpp | CMenuManager::PrintController | 0 | 0 | 228 | 0% | too few |
| Frontend.cpp | CMenuManager::Draw | 44 | 37 | 73 | 54% | not ready |
| Frontend.cpp | CMenuManager::PrintMap | 0 | 0 | 108 | 0% | too few |
| Frontend.cpp | CMenuManager::DrawPlayerSetupScreen | 0 | 0 | 88 | 0% | too few |
| Frontend.cpp | CMenuManager::DrawControllerBound | 0 | 0 | 63 | 0% | too few |
| Frontend.cpp | CMenuManager::DrawControllerSetupScreen | 0 | 0 | 47 | 0% | too few |
| Frontend.cpp | CMenuManager::ProcessList | 0 | 0 | 43 | 0% | too few |
| Frontend.cpp | CMenuManager::Process | 7 | 8 | 27 | 47% | not ready |
| Frontend.cpp | CMenuManager::LoadAllTextures | 10 | 23 | 6 | 30% | not ready |
| Frontend.cpp | CMenuManager::ConstructStatLine | 0 | 0 | 38 | 0% | too few |
| Frontend.cpp | CMenuManager::ProcessOnOffMenuOptions | 0 | 0 | 31 | 0% | too few |
| Frontend.cpp | CMenuManager::CheckCodesForControls | 0 | 0 | 29 | 0% | too few |
| Frontend.cpp | CMenuManager::DrawControllerScreenExtraText | 0 | 0 | 29 | 0% | too few |
| Frontend.cpp | CMenuManager::DrawFrontEndNormal | 12 | 6 | 11 | 67% | not ready |
| Frontend.cpp | CMenuManager::PrintStats | 0 | 0 | 21 | 0% | too few |
| Frontend.cpp | CMenuManager::LoadController | 4 | 11 | 2 | 27% | not ready |
| Frontend.cpp | CMenuManager::DisplayHelperText | 0 | 0 | 17 | 0% | too few |
| Frontend.cpp | CMenuManager::MessageScreen | 0 | 0 | 17 | 0% | too few |
| Frontend.cpp | CMenuManager::CheckSliderMovement | 0 | 0 | 16 | 0% | too few |
| Frontend.cpp | CMenuManager::DisplaySlider | 0 | 0 | 16 | 0% | too few |
| Frontend.cpp | CMenuManager::ThingsToDoBeforeGoingBack | 3 | 5 | 6 | 38% | not ready |
| Frontend.cpp | CMenuManager::LoadSettings | 1 | 7 | 5 | 12% | not ready |
| Frontend.cpp | CMenuManager::InitialiseChangedLanguageSettings | 0 | 0 | 12 | 0% | too few |
| Frontend.cpp | CMenuManager::PrintBriefs | 0 | 5 | 6 | 0% | not ready |
| Frontend.cpp | CMenuManager::SwitchMenuOnAndOff | 2 | 7 | 2 | 22% | not ready |
| Frontend.cpp | CMenuManager::UnloadTextures | 0 | 10 | 0 | 0% | not ready |
| Frontend.cpp | CMenuManager::PrintErrorMessage | 0 | 0 | 10 | 0% | too few |
| Frontend.cpp | CMenuManager::CheckHover | 0 | 0 | 8 | 0% | too few |
| Frontend.cpp | CMenuManager::FilterOutColorMarkersFromString | 0 | 0 | 8 | 0% | too few |
| Frontend.cpp | CMenuManager::DoSettingsBeforeStartingAGame | 0 | 0 | 8 | 0% | too few |
| Frontend.cpp | CMenuManager::GetPreviousPageOption | 6 | 2 | 0 | 75% | careful |
| Frontend.cpp | CMenuManager::ScrollDownListByOne | 0 | 0 | 7 | 0% | too few |
| Frontend.cpp | CMenuManager::DrawFrontEnd | 4 | 2 | 0 | 67% | not ready |
| Frontend.cpp | CMenuManager::PickNewPlayerColour | 0 | 0 | 6 | 0% | too few |
| Frontend.cpp | GetOptionCount | 0 | 4 | 0 | 0% | too few |
| Frontend.cpp | CMenuManager::PageUpList | 0 | 0 | 4 | 0% | too few |
| Frontend.cpp | ScreenHasOption | 1 | 3 | 0 | 25% | too few |
| Frontend.cpp | CMenuManager::PageDownList | 0 | 0 | 3 | 0% | too few |
| Frontend.cpp | CMenuManager::WaitForUserCD | 0 | 0 | 3 | 0% | too few |
| Frontend.cpp | CMenuManager::FadeIn | 3 | 0 | 0 | 100% | too few |
| Frontend.cpp | CMenuManager::ScrollUpListByOne | 0 | 0 | 3 | 0% | too few |
| Frontend.cpp | CMenuManager::BuildStatLine | 0 | 0 | 2 | 0% | too few |
| Frontend.cpp | CMenuManager::RequestFrontEndShutDown | 0 | 1 | 0 | 0% | too few |
| Frontend.cpp | CMenuManager::ShutdownJustMenu | 1 | 0 | 0 | 100% | too few |
| Frontend.cpp | CMenuManager::SaveSettings | 0 | 1 | 0 | 0% | too few |
| Ped.cpp | CPed::ProcessControl | 188 | 137 | 93 | 58% | not ready |
| Ped.cpp | CPed::SetDirectionToWalkAroundObject | 77 | 48 | 19 | 62% | not ready |
| Ped.cpp | CPed::ScanForInterestingStuff | 23 | 8 | 49 | 74% | not ready |
| Ped.cpp | CPed::Wait | 36 | 4 | 38 | 90% | ready |
| Ped.cpp | CPed::Flee | 60 | 13 | 2 | 82% | careful |
| Ped.cpp | CPed::SeekCar | 22 | 26 | 24 | 46% | not ready |
| Ped.cpp | CPed::Seek | 35 | 23 | 6 | 60% | not ready |
| Ped.cpp | CPed::LookForInterestingNodes | 15 | 36 | 11 | 29% | not ready |
| Ped.cpp | CPed::PedSetInCarCB | 33 | 21 | 7 | 61% | not ready |
| Ped.cpp | CPed::ProcessEntityCollision | 23 | 31 | 0 | 43% | not ready |
| Ped.cpp | CPed::SetWaitState | 24 | 9 | 18 | 73% | not ready |
| Ped.cpp | CPed::PlayFootSteps | 27 | 6 | 14 | 82% | careful |
| Ped.cpp | CPed::PedSetOutCarCB | 27 | 8 | 10 | 77% | careful |
| Ped.cpp | CPed::ProcessBuoyancy | 20 | 21 | 1 | 49% | not ready |
| Ped.cpp | CPed::MoveHeadToLook | 23 | 12 | 1 | 66% | not ready |
| Ped.cpp | CPed::WanderPath | 17 | 7 | 10 | 71% | not ready |
| Ped.cpp | CPed::FinishLaunchCB | 12 | 2 | 17 | 86% | careful |
| Ped.cpp | CPed::PossiblyFindBetterPosToSeekCar | 12 | 19 | 0 | 39% | not ready |
| Ped.cpp | CPed::BuildPedLists | 25 | 3 | 2 | 89% | careful |
| Ped.cpp | CPed::PreRender | 8 | 17 | 3 | 32% | not ready |
| Ped.cpp | CPed::ScanForThreats | 10 | 12 | 5 | 45% | not ready |
| Ped.cpp | CPed::SetEvasiveDive | 13 | 8 | 2 | 62% | not ready |
| Ped.cpp | CPed::Avoid | 19 | 4 | 0 | 83% | careful |
| Ped.cpp | CPed::WarpPedIntoCar | 7 | 9 | 6 | 44% | not ready |
| Ped.cpp | CPed::SetEvasiveStep | 19 | 2 | 0 | 90% | ready |
| Ped.cpp | CPed::SetFall | 11 | 3 | 7 | 79% | careful |
| Ped.cpp | CPed::UpdatePosition | 5 | 7 | 8 | 42% | not ready |
| Ped.cpp | CPed::PedEvadeCB | 12 | 4 | 4 | 75% | careful |
| Ped.cpp | CPed::~CPed | 12 | 7 | 1 | 63% | not ready |
| Ped.cpp | CPed::SetSeek | 16 | 2 | 1 | 89% | careful |
| Ped.cpp | CPed::Idle | 5 | 13 | 1 | 28% | not ready |
| Ped.cpp | CPed::SetMoveAnim | 13 | 4 | 2 | 76% | careful |
| Ped.cpp | CPed::Chat | 11 | 3 | 4 | 79% | careful |
| Ped.cpp | CPed::SetDie | 12 | 3 | 3 | 80% | careful |
| Ped.cpp | CPed::LookForSexyPeds | 15 | 2 | 0 | 88% | careful |
| Ped.cpp | CPed::CalculateNewVelocity | 12 | 5 | 0 | 71% | not ready |
| Ped.cpp | CPed::SortPeds | 14 | 2 | 0 | 88% | careful |
| Ped.cpp | CPed::Solicit | 0 | 0 | 16 | 0% | too few |
| Ped.cpp | CPed::LookForSexyCars | 15 | 1 | 0 | 94% | ready |
| Ped.cpp | CPed::SetGetUp | 10 | 4 | 1 | 71% | not ready |
| Ped.cpp | CPed::RestorePreviousState | 8 | 4 | 3 | 67% | not ready |
| Ped.cpp | CPed::SetPedPositionInCar | 8 | 0 | 7 | 100% | ready |
| Ped.cpp | CPed::SetFlee | 10 | 4 | 0 | 71% | not ready |
| Ped.cpp | CPed::FacePhone | 0 | 0 | 13 | 0% | too few |
| Ped.cpp | CPed::CheckAroundForPossibleCollisions | 0 | 0 | 13 | 0% | too few |
| Ped.cpp | CPed::SetFollowPath | 0 | 0 | 12 | 0% | too few |
| Ped.cpp | CPed::PedSetDraggedOutCarCB | 6 | 5 | 1 | 55% | not ready |
| Ped.cpp | CPed::SetWanderPath | 4 | 0 | 7 | 100% | too few |
| Ped.cpp | CPed::Save | 0 | 0 | 10 | 0% | too few |
| Ped.cpp | CPed::SetRadioStation | 6 | 0 | 4 | 100% | ready |
| Ped.cpp | CPed::CanPedDriveOff | 4 | 5 | 1 | 44% | not ready |
| Ped.cpp | CPed::Load | 0 | 0 | 10 | 0% | too few |
| Ped.cpp | CPed::PedGetupCB | 5 | 3 | 1 | 62% | not ready |
| Ped.cpp | CPed::Mug | 0 | 0 | 9 | 0% | too few |
| Ped.cpp | CPed::SetSolicit | 0 | 0 | 9 | 0% | too few |
| Ped.cpp | CPed::CanStrafeOrMouseControl | 8 | 0 | 0 | 100% | ready |
| Ped.cpp | CPed::SetDead | 5 | 3 | 0 | 62% | not ready |
| Ped.cpp | CPed::InTheAir | 5 | 3 | 0 | 62% | not ready |
| Ped.cpp | CPed::CanPedReturnToState | 7 | 1 | 0 | 88% | careful |
| Ped.cpp | CPed::CPed | 4 | 3 | 0 | 57% | not ready |
| Ped.cpp | CPed::SetJump | 4 | 3 | 0 | 57% | not ready |
| Ped.cpp | CPed::WorkOutHeadingForMovingFirstPerson | 7 | 0 | 0 | 100% | ready |
| Ped.cpp | CPed::SetLookFlag | 4 | 3 | 0 | 57% | not ready |
| Ped.cpp | CPed::SetIdle | 6 | 1 | 0 | 86% | careful |
| Ped.cpp | CPed::SetChat | 7 | 0 | 0 | 100% | ready |
| Ped.cpp | CPed::GiveWeapon | 1 | 6 | 0 | 14% | not ready |
| Ped.cpp | CPed::FlagToDestroyWhenNextProcessed | 3 | 3 | 1 | 50% | not ready |
| Ped.cpp | CPed::SetStoredState | 3 | 3 | 0 | 50% | not ready |
| Ped.cpp | CPed::WillChat | 4 | 2 | 0 | 67% | not ready |
| Ped.cpp | CPed::SetSeekCar | 3 | 3 | 0 | 50% | not ready |
| Ped.cpp | CPed::Render | 0 | 3 | 3 | 0% | too few |
| Ped.cpp | CPed::WanderRange | 0 | 0 | 6 | 0% | too few |
| Ped.cpp | CPed::GetLocalDirection | 4 | 1 | 0 | 80% | careful |
| Ped.cpp | CPed::SetInTheAir | 2 | 2 | 1 | 50% | too few |
| Ped.cpp | CPed::SetModelIndex | 4 | 0 | 1 | 100% | too few |
| Ped.cpp | CPed::ClearWeapons | 2 | 3 | 0 | 40% | not ready |
| Ped.cpp | CPed::ClearLookFlag | 4 | 0 | 1 | 100% | too few |
| Ped.cpp | CPed::IsPointerValid | 2 | 3 | 0 | 40% | not ready |
| Ped.cpp | CPed::SetLanding | 5 | 0 | 0 | 100% | ready |
| Ped.cpp | CPed::ClearAll | 2 | 3 | 0 | 40% | not ready |
| Ped.cpp | CPed::SetBuyIceCream | 0 | 0 | 4 | 0% | too few |
| Ped.cpp | CPed::AimGun | 4 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::IsGangMember | 1 | 3 | 0 | 25% | too few |
| Ped.cpp | CPed::UseGroundColModel | 4 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::OurPedCanSeeThisOne | 2 | 2 | 0 | 50% | too few |
| Ped.cpp | CPed::TurnBody | 3 | 1 | 0 | 75% | too few |
| Ped.cpp | CPed::IsPedInControl | 3 | 1 | 0 | 75% | too few |
| Ped.cpp | CPed::IsPlayer | 4 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::CheckForExplosions | 1 | 1 | 1 | 50% | too few |
| Ped.cpp | CPed::Initialise | 2 | 1 | 0 | 67% | too few |
| Ped.cpp | CPed::Pause | 0 | 0 | 3 | 0% | too few |
| Ped.cpp | CPed::SetLookTimer | 3 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::Fall | 3 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::CanPedJumpThis | 2 | 1 | 0 | 67% | too few |
| Ped.cpp | CPed::Teleport | 2 | 1 | 0 | 67% | too few |
| Ped.cpp | CPed::SetShootTimer | 2 | 1 | 0 | 67% | too few |
| Ped.cpp | FinishFuckUCB | 0 | 3 | 0 | 0% | too few |
| Ped.cpp | particleProduceFootSplash | 3 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::FollowPath | 0 | 0 | 3 | 0% | too few |
| Ped.cpp | CPed::MakePhonecall | 0 | 0 | 3 | 0% | too few |
| Ped.cpp | particleProduceFootDust | 3 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::IsPedShootable | 1 | 1 | 0 | 50% | too few |
| Ped.cpp | CPed::ClearLook | 0 | 0 | 2 | 0% | too few |
| Ped.cpp | CPed::SetAttackTimer | 1 | 1 | 0 | 50% | too few |
| Ped.cpp | CPed::SetAimFlag | 0 | 2 | 0 | 0% | too few |
| Ped.cpp | CPed::CheckIfInTheAir | 1 | 1 | 0 | 50% | too few |
| Ped.cpp | CPed::AddWeaponModel | 1 | 0 | 1 | 100% | too few |
| Ped.cpp | CPed::FinishedWaitCB | 1 | 1 | 0 | 50% | too few |
| Ped.cpp | CPed::SeekFollowingPath | 0 | 2 | 0 | 0% | too few |
| Ped.cpp | CPed::PedLandCB | 2 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::GrantAmmo | 0 | 0 | 2 | 0% | too few |
| Ped.cpp | CPed::operator delete | 1 | 0 | 1 | 100% | too few |
| Ped.cpp | CPed::SetAmmo | 0 | 0 | 2 | 0% | too few |
| Ped.cpp | CPed::ClearChat | 1 | 1 | 0 | 50% | too few |
| Ped.cpp | CPed::SetCurrentWeapon | 0 | 2 | 0 | 0% | too few |
| Ped.cpp | CPed::CanSetPedState | 2 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::FinishHitHeadCB | 2 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::RestartNonPartialAnims | 0 | 1 | 0 | 0% | too few |
| Ped.cpp | CPed::CalculateNewOrientation | 1 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::CheckForGunShots | 1 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::ClearPause | 0 | 0 | 1 | 0% | too few |
| Ped.cpp | CPed::ClearFlee | 1 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::SetLeader | 0 | 0 | 1 | 0% | too few |
| Ped.cpp | CPed::ClearFall | 1 | 0 | 0 | 100% | too few |
| Ped.cpp | CPed::ClearSeek | 0 | 0 | 1 | 0% | too few |
| Ped.cpp | CPed::CheckForDeadPeds | 1 | 0 | 0 | 100% | too few |
| PedAI.cpp | CPed::ProcessObjective | 140 | 53 | 293 | 73% | not ready |
| PedAI.cpp | CPed::SetObjective | 13 | 21 | 59 | 38% | not ready |
| PedAI.cpp | CPed::LineUpPedWithCar | 44 | 14 | 7 | 76% | careful |
| PedAI.cpp | CPed::UpdateFromLeader | 0 | 2 | 58 | 0% | too few |
| PedAI.cpp | CPed::ReactToPointGun | 0 | 1 | 50 | 0% | too few |
| PedAI.cpp | CPed::PedAnimDoorOpenCB | 20 | 8 | 18 | 71% | not ready |
| PedAI.cpp | CPed::SetExitCar | 21 | 9 | 13 | 70% | not ready |
| PedAI.cpp | CPed::PedAnimGetInCB | 19 | 13 | 10 | 59% | not ready |
| PedAI.cpp | CPed::DuckAndCover | 25 | 10 | 1 | 71% | not ready |
| PedAI.cpp | CPed::PedSetQuickDraggedOutCarPositionCB | 16 | 3 | 7 | 84% | careful |
| PedAI.cpp | CPed::SetAnimOffsetForEnterOrExitVehicle | 4 | 20 | 0 | 17% | not ready |
| PedAI.cpp | CPed::SetEnterCar_AllClear | 7 | 12 | 2 | 37% | not ready |
| PedAI.cpp | CPed::ReactToAttack | 9 | 7 | 5 | 56% | not ready |
| PedAI.cpp | CPed::PedAnimAlignCB | 14 | 3 | 3 | 82% | careful |
| PedAI.cpp | CPed::PedSetDraggedOutCarPositionCB | 6 | 1 | 13 | 86% | careful |
| PedAI.cpp | CPed::ExitCar | 14 | 6 | 0 | 70% | not ready |
| PedAI.cpp | CPed::RegisterThreatWithGangPeds | 7 | 1 | 11 | 88% | careful |
| PedAI.cpp | CPed::SetCarJack_AllClear | 9 | 8 | 0 | 53% | not ready |
| PedAI.cpp | CPed::PositionPedOutOfCollision | 10 | 6 | 1 | 62% | not ready |
| PedAI.cpp | CPed::WarpPedToNearLeaderOffScreen | 0 | 0 | 15 | 0% | too few |
| PedAI.cpp | CPed::WarpPedToNearEntityOffScreen | 0 | 0 | 15 | 0% | too few |
| PedAI.cpp | CPed::PedAnimDoorCloseCB | 6 | 2 | 6 | 75% | careful |
| PedAI.cpp | CPed::SelectGunIfArmed | 0 | 0 | 14 | 0% | too few |
| PedAI.cpp | SelectClosestNodeForSeek | 0 | 0 | 13 | 0% | too few |
| PedAI.cpp | CPed::SetBeingDraggedFromCar | 9 | 4 | 0 | 69% | not ready |
| PedAI.cpp | CPed::InformMyGangOfAttack | 1 | 9 | 2 | 10% | not ready |
| PedAI.cpp | CPed::GetNextPointOnRoute | 0 | 0 | 12 | 0% | too few |
| PedAI.cpp | CPed::SetCarJack | 8 | 2 | 0 | 80% | careful |
| PedAI.cpp | CPed::PedAnimPullPedOutCB | 3 | 2 | 5 | 60% | not ready |
| PedAI.cpp | CPed::SetDuck | 0 | 0 | 10 | 0% | too few |
| PedAI.cpp | CPed::PedAnimStepOutCarCB | 7 | 2 | 1 | 78% | careful |
| PedAI.cpp | CPed::SetExitBoat | 4 | 3 | 2 | 57% | not ready |
| PedAI.cpp | CPed::GetLocalPositionToOpenCarDoor | 6 | 3 | 0 | 67% | not ready |
| PedAI.cpp | CPed::GetNearestDoor | 2 | 5 | 2 | 29% | not ready |
| PedAI.cpp | CPed::BeingDraggedFromCar | 4 | 4 | 0 | 50% | not ready |
| PedAI.cpp | CPed::QuitEnteringCar | 3 | 4 | 0 | 43% | not ready |
| PedAI.cpp | CPed::RestorePreviousObjective | 2 | 4 | 1 | 33% | not ready |
| PedAI.cpp | CPed::PedSetOutTrainCB | 0 | 0 | 7 | 0% | too few |
| PedAI.cpp | CPed::CanSeeEntity | 4 | 3 | 0 | 57% | not ready |
| PedAI.cpp | CPed::GetNearestTrainPedPosition | 0 | 0 | 6 | 0% | too few |
| PedAI.cpp | CPed::ClearObjective | 3 | 1 | 2 | 75% | too few |
| PedAI.cpp | CPed::SetEnterTrain | 0 | 0 | 6 | 0% | too few |
| PedAI.cpp | CPed::LineUpPedWithTrain | 0 | 0 | 6 | 0% | too few |
| PedAI.cpp | CPed::SetEnterCar | 3 | 1 | 2 | 75% | too few |
| PedAI.cpp | CPed::EnterCar | 3 | 1 | 2 | 75% | too few |
| PedAI.cpp | CPed::SetSeekBoatPosition | 2 | 3 | 0 | 40% | not ready |
| PedAI.cpp | CPed::SetExitTrain | 0 | 0 | 5 | 0% | too few |
| PedAI.cpp | CPed::GetNearestPassengerDoor | 3 | 2 | 0 | 60% | not ready |
| PedAI.cpp | CPed::SetObjectiveTimer | 2 | 2 | 0 | 50% | too few |
| PedAI.cpp | CPed::PedSetInTrainCB | 0 | 0 | 4 | 0% | too few |
| PedAI.cpp | CPed::PedAnimDoorCloseRollingCB | 1 | 1 | 2 | 50% | too few |
| PedAI.cpp | CPed::IsTemporaryObjective | 3 | 1 | 0 | 75% | too few |
| PedAI.cpp | CPed::ClearDuck | 0 | 0 | 4 | 0% | too few |
| PedAI.cpp | CPed::ClearLeader | 0 | 0 | 4 | 0% | too few |
| PedAI.cpp | CPed::FindBestCoordsFromNodes | 0 | 0 | 3 | 0% | too few |
| PedAI.cpp | CPed::GoToNearestDoor | 3 | 0 | 0 | 100% | too few |
| PedAI.cpp | CPed::Duck | 2 | 1 | 0 | 67% | too few |
| PedAI.cpp | CPed::SeekBoatPosition | 2 | 0 | 1 | 100% | too few |
| PedAI.cpp | AddYardieDoorSmoke | 0 | 0 | 2 | 0% | too few |
| PedAI.cpp | CPed::ForceStoredObjective | 0 | 2 | 0 | 0% | too few |
| PedAI.cpp | CPed::HaveReachedNextPointOnRoute | 0 | 0 | 2 | 0% | too few |
| PedAI.cpp | CPed::SetStoredObjective | 0 | 1 | 0 | 0% | too few |
| PedAI.cpp | CPed::IsRoomToBeCarJacked | 0 | 1 | 0 | 0% | too few |
| PedAI.cpp | CPed::EnterTrain | 0 | 0 | 1 | 0% | too few |
| PedAI.cpp | CPed::SetPedPositionInTrain | 0 | 0 | 1 | 0% | too few |
| PedAI.cpp | CPed::ExitTrain | 0 | 0 | 1 | 0% | too few |
| PedAI.cpp | CPed::GetFormationPosition | 0 | 0 | 1 | 0% | too few |
| Automobile.cpp | CAutomobile::ProcessControl | 219 | 123 | 108 | 64% | not ready |
| Automobile.cpp | CAutomobile::PreRender | 211 | 127 | 31 | 62% | not ready |
| Automobile.cpp | CAutomobile::HydraulicControl | 0 | 0 | 202 | 0% | too few |
| Automobile.cpp | CAutomobile::VehicleDamage | 96 | 29 | 17 | 77% | careful |
| Automobile.cpp | CAutomobile::Render | 24 | 67 | 26 | 26% | not ready |
| Automobile.cpp | CAutomobile::ProcessBuoyancy | 15 | 15 | 34 | 50% | not ready |
| Automobile.cpp | CAutomobile::SpawnFlyingComponent | 33 | 10 | 0 | 77% | careful |
| Automobile.cpp | CAutomobile::ProcessControlInputs | 12 | 6 | 23 | 67% | not ready |
| Automobile.cpp | CAutomobile::TankControl | 26 | 13 | 2 | 67% | not ready |
| Automobile.cpp | CAutomobile::CAutomobile | 24 | 10 | 7 | 71% | not ready |
| Automobile.cpp | CAutomobile::ProcessEntityCollision | 21 | 6 | 7 | 78% | careful |
| Automobile.cpp | CAutomobile::PlaceOnRoadProperly | 0 | 0 | 31 | 0% | too few |
| Automobile.cpp | CAutomobile::BlowUpCar | 23 | 4 | 1 | 85% | careful |
| Automobile.cpp | CAutomobile::SetupSuspensionLines | 23 | 2 | 3 | 92% | ready |
| Automobile.cpp | CAutomobile::FireTruckControl | 4 | 6 | 16 | 40% | not ready |
| Automobile.cpp | CPed::MakeTyresMuddySectorList | 4 | 17 | 3 | 19% | not ready |
| Automobile.cpp | CAutomobile::ProcessAutoBusDoors | 0 | 0 | 24 | 0% | too few |
| Automobile.cpp | ProcessDoorOpenCloseAnimation | 17 | 7 | 0 | 71% | not ready |
| Automobile.cpp | CAutomobile::AddDamagedVehicleParticles | 10 | 9 | 2 | 53% | not ready |
| Automobile.cpp | CAutomobile::DoDriveByShootings | 2 | 6 | 12 | 25% | not ready |
| Automobile.cpp | CAutomobile::HasCarStoppedBecauseOfLight | 14 | 4 | 0 | 78% | careful |
| Automobile.cpp | CAutomobile::AddWheelDirtAndWater | 6 | 1 | 10 | 86% | careful |
| Automobile.cpp | CAutomobile::IsRoomForPedToLeaveCar | 6 | 11 | 0 | 35% | not ready |
| Automobile.cpp | CPed::DeadPedMakesTyresBloody | 2 | 15 | 0 | 12% | not ready |
| Automobile.cpp | CAutomobile::RcbanditCheck1CarWheels | 0 | 0 | 16 | 0% | too few |
| Automobile.cpp | CAutomobile::dmgDrawCarCollidingParticles | 16 | 0 | 0 | 100% | ready |
| Automobile.cpp | CAutomobile::RcbanditCheckHitWheels | 0 | 0 | 15 | 0% | too few |
| Automobile.cpp | CAutomobile::OpenDoor | 10 | 4 | 0 | 71% | not ready |
| Automobile.cpp | ProcessDoorCloseAnimation | 10 | 4 | 0 | 71% | not ready |
| Automobile.cpp | ProcessDoorOpenAnimation | 9 | 4 | 0 | 69% | not ready |
| Automobile.cpp | CAutomobile::SetupDamageAfterLoad | 0 | 0 | 12 | 0% | too few |
| Automobile.cpp | CAutomobile::ProcessOpenDoor | 5 | 0 | 7 | 100% | ready |
| Automobile.cpp | CAutomobile::SetUpWheelColModel | 0 | 0 | 12 | 0% | too few |
| Automobile.cpp | CAutomobile::Fix | 0 | 0 | 10 | 0% | too few |
| Automobile.cpp | CAutomobile::BlowUpCarsInPath | 6 | 1 | 0 | 86% | careful |
| Automobile.cpp | CAutomobile::SetDoorDamage | 3 | 3 | 1 | 50% | not ready |
| Automobile.cpp | CAutomobile::BurstTyre | 0 | 0 | 7 | 0% | too few |
| Automobile.cpp | CAutomobile::Teleport | 4 | 3 | 0 | 57% | not ready |
| Automobile.cpp | CAutomobile::PlayCarHorn | 7 | 0 | 0 | 100% | ready |
| Automobile.cpp | CAutomobile::RemoveBonnetInPedCollision | 0 | 1 | 5 | 0% | too few |
| Automobile.cpp | CAutomobile::ProcessSwingingDoor | 5 | 0 | 0 | 100% | ready |
| Automobile.cpp | CAutomobile::SetBusDoorTimer | 0 | 0 | 5 | 0% | too few |
| Automobile.cpp | CAutomobile::Load | 0 | 0 | 5 | 0% | too few |
| Automobile.cpp | CAutomobile::SetComponentRotation | 0 | 0 | 5 | 0% | too few |
| Automobile.cpp | CAutomobile::SetupModelNodes | 2 | 2 | 0 | 50% | too few |
| Automobile.cpp | CAutomobile::SetBumperDamage | 3 | 1 | 0 | 75% | too few |
| Automobile.cpp | CAutomobile::RemoveRefsToVehicle | 0 | 0 | 4 | 0% | too few |
| Automobile.cpp | CAutomobile::SetPanelDamage | 2 | 2 | 0 | 50% | too few |
| Automobile.cpp | CAutomobile::Save | 0 | 0 | 3 | 0% | too few |
| Automobile.cpp | CAutomobile::ScanForCrimes | 0 | 0 | 3 | 0% | too few |
| Automobile.cpp | CAutomobile::ResetSuspension | 1 | 2 | 0 | 33% | too few |
| Automobile.cpp | CAutomobile::SetModelIndex | 2 | 0 | 0 | 100% | too few |
| Automobile.cpp | CAutomobile::SetComponentVisibility | 0 | 1 | 0 | 0% | too few |
| Automobile.cpp | CAutomobile::IsDoorMissing | 1 | 0 | 0 | 100% | too few |
| Automobile.cpp | CAutomobile::ReduceHornCounter | 1 | 0 | 0 | 100% | too few |
| Automobile.cpp | CAutomobile::IsDoorReady | 0 | 1 | 0 | 0% | too few |
| Automobile.cpp | CAutomobile::GetAllWheelsOffGround | 0 | 0 | 1 | 0% | too few |
| Automobile.cpp | CAutomobile::PlayHornIfNecessary | 1 | 0 | 0 | 100% | too few |
| Automobile.cpp | SetVehicleAtomicVisibilityCB | 1 | 0 | 0 | 100% | too few |

## Operators

| Operator | Killed | Survived | No coverage | Covered score |
| --- | --- | --- | --- | --- |
| cxx_remove_void_call | 948 | 481 | 1795 | 66% |
| cxx_eq_to_ne | 738 | 326 | 361 | 69% |
| cxx_mul_to_div | 472 | 194 | 379 | 71% |
| cxx_add_to_sub | 461 | 119 | 443 | 79% |
| cxx_lt_to_le | 116 | 366 | 241 | 24% |
| cxx_lt_to_ge | 384 | 98 | 241 | 80% |
| cxx_sub_to_add | 316 | 89 | 311 | 78% |
| cxx_ne_to_eq | 308 | 139 | 220 | 69% |
| cxx_gt_to_le | 358 | 85 | 210 | 81% |
| cxx_gt_to_ge | 116 | 327 | 210 | 26% |
| cxx_div_to_mul | 124 | 42 | 120 | 75% |
| cxx_post_inc_to_post_dec | 160 | 27 | 89 | 86% |
| cxx_le_to_lt | 25 | 102 | 36 | 20% |
| cxx_le_to_gt | 97 | 30 | 36 | 76% |
| cxx_minus_to_noop | 69 | 31 | 52 | 69% |
| cxx_rem_to_div | 57 | 7 | 78 | 89% |
| cxx_ge_to_gt | 18 | 85 | 34 | 17% |
| cxx_ge_to_lt | 73 | 30 | 34 | 71% |
| cxx_pre_inc_to_pre_dec | 9 | 7 | 22 | 56% |

## Survivors (first 60)

- src/control/CarCtrl.cpp:827 CCarCtrl::UpdateCarOnRails `*` -> `/` (cxx_mul_to_div)
- src/peds/Ped.cpp:3505 CPed::GetLocalDirection `<` -> `<=` (cxx_lt_to_le)
- src/control/CarCtrl.cpp:2191 CCarCtrl::SteerAICarWithPhysics_OnlyMission `==` -> `!=` (cxx_eq_to_ne)
- src/control/CarCtrl.cpp:1838 CCarCtrl::PickNextNodeToChaseCar `+` -> `-` (cxx_add_to_sub)
- src/peds/Ped.cpp:7182 CPed::LookForInterestingNodes `>=` -> `>` (cxx_ge_to_gt)
- src/control/CarCtrl.cpp:2519 CCarCtrl::RegisterVehicleOfInterest `<` -> `<=` (cxx_lt_to_le)
- src/audio/AudioLogic.cpp:3065 cAudioManager::SetupJumboEngineSound `<` -> `<=` (cxx_lt_to_le)
- src/audio/AudioLogic.cpp:454 cAudioManager::ProcessSpecial `SampleManager.SetEffectsFadeVolume(MAX_VOLUME)` -> `((void)0)` (cxx_remove_void_call)
- src/control/CarCtrl.cpp:555 CCarCtrl::GenerateOneRandomCar `*` -> `/` (cxx_mul_to_div)
- src/peds/Ped.cpp:3094 CPed::ProcessEntityCollision `>=` -> `>` (cxx_ge_to_gt)
- src/peds/PedAI.cpp:311 CPed::SetObjective `==` -> `!=` (cxx_eq_to_ne)
- src/peds/Ped.cpp:4617 CPed::PedSetInCarCB `==` -> `!=` (cxx_eq_to_ne)
- src/vehicles/Automobile.cpp:4531 CAutomobile::SpawnFlyingComponent `>` -> `>=` (cxx_gt_to_ge)
- src/control/CarCtrl.cpp:1671 CCarCtrl::PickNextNodeRandomly `<` -> `<=` (cxx_lt_to_le)
- src/core/Cam.cpp:3623 CCam::Process_FlyBy `-` -> `+` (cxx_sub_to_add)
- src/peds/Ped.cpp:5639 CPed::SetFlee `SetMoveState(PEDMOVE_RUN)` -> `((void)0)` (cxx_remove_void_call)
- src/peds/PedAI.cpp:3447 CPed::BeingDraggedFromCar `<=` -> `<` (cxx_le_to_lt)
- src/vehicles/Automobile.cpp:1526 CAutomobile::PreRender `<` -> `<=` (cxx_lt_to_le)
- src/vehicles/Automobile.cpp:4625 CAutomobile::SetDoorDamage `==` -> `!=` (cxx_eq_to_ne)
- src/core/Frontend.cpp:3739 CMenuManager::LoadController `m_aFrontEndSprites[i].SetAddressing(rwTEXTUREADDRESSBORDER)` -> `((void)0)` (cxx_remove_void_call)
- src/control/CarCtrl.cpp:138 CCarCtrl::GenerateOneRandomCar `>=` -> `>` (cxx_ge_to_gt)
- src/peds/Ped.cpp:4048 CPed::SetDirectionToWalkAroundObject `!=` -> `==` (cxx_ne_to_eq)
- src/audio/AudioLogic.cpp:8644 cAudioManager::ProcessBridgeOneShots `==` -> `!=` (cxx_eq_to_ne)
- src/peds/Ped.cpp:5177 CPed::SetInTheAir `==` -> `!=` (cxx_eq_to_ne)
- src/control/CarCtrl.cpp:1896 CCarCtrl::PickNextNodeToFollowPath `>=` -> `<` (cxx_ge_to_lt)
- src/core/Cam.cpp:3071 CCam::Process_Sniper `<` -> `<=` (cxx_lt_to_le)
- src/peds/PedAI.cpp:2058 CPed::ReactToPointGun `==` -> `!=` (cxx_eq_to_ne)
- src/vehicles/Automobile.cpp:1137 CAutomobile::ProcessControl `==` -> `!=` (cxx_eq_to_ne)
- src/peds/Ped.cpp:3580 CPed::SetDirectionToWalkAroundObject `!=` -> `==` (cxx_ne_to_eq)
- src/vehicles/Automobile.cpp:1771 CAutomobile::PreRender `>` -> `>=` (cxx_gt_to_ge)
- src/peds/Ped.cpp:6713 CPed::SeekCar `==` -> `!=` (cxx_eq_to_ne)
- src/audio/AudioLogic.cpp:8773 cAudioManager::PreloadMissionAudio `*` -> `/` (cxx_mul_to_div)
- src/core/Cam.cpp:3311 CCam::Process_BehindBoat `-` -> ` ` (cxx_minus_to_noop)
- src/peds/Ped.cpp:6834 CPed::SeekCar `==` -> `!=` (cxx_eq_to_ne)
- src/control/CarCtrl.cpp:552 CCarCtrl::GenerateOneRandomCar `*` -> `/` (cxx_mul_to_div)
- src/control/CarCtrl.cpp:2823 CCarCtrl::MapCouldMoveInThisArea `>` -> `<=` (cxx_gt_to_le)
- src/peds/PedAI.cpp:1945 CPed::ProcessObjective `>` -> `<=` (cxx_gt_to_le)
- src/vehicles/Automobile.cpp:4437 CAutomobile::SpawnFlyingComponent `>=` -> `>` (cxx_ge_to_gt)
- src/vehicles/Automobile.cpp:3413 CAutomobile::VehicleDamage `>` -> `>=` (cxx_gt_to_ge)
- src/control/CarCtrl.cpp:2689 CCarCtrl::GenerateEmergencyServicesCar `CStreaming::SetModelIsDeletable(MI_FIREMAN)` -> `((void)0)` (cxx_remove_void_call)
- src/peds/Ped.cpp:7882 CPed::PossiblyFindBetterPosToSeekCar `-` -> `+` (cxx_sub_to_add)
- src/core/Frontend.cpp:3587 CMenuManager::LoadAllTextures `DMAudio.ChangeMusicMode(MUSICMODE_FRONTEND)` -> `((void)0)` (cxx_remove_void_call)
- src/core/Cam.cpp:1962 CCam::WorkOutCamHeight `<` -> `<=` (cxx_lt_to_le)
- src/vehicles/Automobile.cpp:1857 CAutomobile::PreRender `==` -> `!=` (cxx_eq_to_ne)
- src/core/Frontend.cpp:3704 CMenuManager::LoadController `<=` -> `<` (cxx_le_to_lt)
- src/vehicles/Automobile.cpp:4236 CPed::MakeTyresMuddySectorList `-` -> `+` (cxx_sub_to_add)
- src/control/CarCtrl.cpp:2397 CCarCtrl::SteerAICarWithPhysicsFollowPath `<` -> `<=` (cxx_lt_to_le)
- src/vehicles/Automobile.cpp:628 CAutomobile::ProcessControl `==` -> `!=` (cxx_eq_to_ne)
- src/audio/AudioLogic.cpp:346 cAudioManager::PreTerminateGameSpecificShutdown `>=` -> `>` (cxx_ge_to_gt)
- src/control/CarCtrl.cpp:2664 CCarCtrl::GenerateEmergencyServicesCar `+` -> `-` (cxx_add_to_sub)
- src/core/Cam.cpp:813 CCam::ClipIfPedInFrontOfPlayer `-` -> `+` (cxx_sub_to_add)
- src/peds/PedAI.cpp:3065 CPed::LineUpPedWithCar `==` -> `!=` (cxx_eq_to_ne)
- src/core/Frontend.cpp:4934 CMenuManager::ProcessButtonPresses `<=` -> `<` (cxx_le_to_lt)
- src/control/CarCtrl.cpp:889 CCarCtrl::FindMaximumSpeedForThisCarInTraffic `/` -> `*` (cxx_div_to_mul)
- src/audio/AudioLogic.cpp:2873 cAudioManager::ProcessPlane `ProcessCesna(params)` -> `((void)0)` (cxx_remove_void_call)
- src/peds/Ped.cpp:4116 CPed::IsPedShootable `<=` -> `<` (cxx_le_to_lt)
- src/core/Cam.cpp:586 CCam::ProcessSpecialHeightRoutines `!=` -> `==` (cxx_ne_to_eq)
- src/peds/PedAI.cpp:5182 CPed::SetSeekBoatPosition `m_carInObjective->RegisterReference((CEntity **) &m_carInObj` -> `((void)0)` (cxx_remove_void_call)
- src/peds/Ped.cpp:8413 CPed::WarpPedIntoCar `StopNonPartialAnims()` -> `((void)0)` (cxx_remove_void_call)
- src/peds/Ped.cpp:2761 CPed::ProcessControl `>` -> `>=` (cxx_gt_to_ge)
