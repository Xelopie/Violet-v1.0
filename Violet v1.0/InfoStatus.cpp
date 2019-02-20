#include "stdafx.h"

void INFOSTATUS::Print()
{
	string espString = "[F1] ESP: ";
	if (ESP::status) espString += "ON";
	else espString += "OFF";

	string recoilCrosshairString = "[F2] RecoilCrosshair: ";
	if (RECOILCROSSHAIR::status) recoilCrosshairString += "ON";
	else recoilCrosshairString += "OFF";

	string chamsString = "[F3] Chams: ";
	if (CHAMS::status) chamsString += "ON";
	else chamsString += "OFF";

	string bhopString = "[F4] Bhop: ";
	if (BHOP::status) bhopString += "ON";
	else bhopString += "OFF";

	string glowString = "[F5] Glow: ";
	if (GLOW::status) glowString += "ON";
	else glowString += "OFF";

	string radarString = "[F6] Radar: ";
	if (RADAR::status) radarString += "ON";
	else radarString += "OFF";

	string aimbotString = "[F7] Aimbot: ";
	if (AIMBOT::status) aimbotString += "ON";
	else aimbotString += "OFF";

	string fovString = "[F8] ChangeFOV (" + to_string(FOV::targetFOV) + ") | NowFOV: " + to_string(LocalPlayer.fov);

	string thirdPersonString = "[F9] ThirdPerson: ";
	if (THIRDPERSON::status) thirdPersonString += "ON";
	else thirdPersonString += "OFF";

	string exitString = "[F10] EXIT";

	string statusOutput = espString + "\n"
		+ recoilCrosshairString + "\n"
		+ chamsString + "\n"
		+ bhopString + "\n"
		+ glowString + "\n"
		+ radarString + "\n"
		+ aimbotString + "\n"
		+ fovString + "\n"
		+ thirdPersonString + "\n"
		+ exitString + "\n"
		+ "Current Overlay Name: " + GLOBAL::lWindowName;

	int x = 0.22*(GLOBAL::rect.right - GLOBAL::rect.left);
	int y = 0.05*(GLOBAL::rect.bottom - GLOBAL::rect.top);

	Overlay.DrawString(statusOutput.c_str(), x, y, COLOR::SkyColor);

	/* Print debug info */
	stringstream clientSS;
	clientSS << "ClientDLL: 0x" << hex << uppercase << GLOBAL::clientDLL.base;
	stringstream engineSS;
	engineSS << "EngineDLL: 0x" << hex << uppercase << GLOBAL::engineDLL.base;
	stringstream localPlayerSS;
	localPlayerSS << "LocalPlayer: 0x" << hex << uppercase << GLOBAL::localPlayerAddy;
	stringstream entityListSS;
	entityListSS << "EntityList: 0x" << hex << uppercase << GLOBAL::entityListAddy;
	stringstream clientStateSS;
	clientStateSS << "ClientState: 0x" << hex << uppercase << GLOBAL::clientStateAddy;
	stringstream clientStateViewAngleSS;
	clientStateViewAngleSS << "ClientStateViewAngle: 0x" << hex << uppercase << GLOBAL::clientStateViewAngleAddy;
	stringstream forceJumpSS;
	forceJumpSS << "ForceJump: 0x" << hex << uppercase << GLOBAL::forceJumpAddy;
	stringstream modelAmbientMinSS;
	modelAmbientMinSS << "ModelAmbientMin: 0x" << hex << uppercase <<GLOBAL::modelAmbientMinAddy;

	string debugOutput = clientSS.str() + "\n"
		+ engineSS.str() + "\n"
		+ localPlayerSS.str() + "\n"
		+ entityListSS.str() + "\n"
		+ clientStateSS.str() + "\n"
		+ clientStateViewAngleSS.str() + "\n"
		+ forceJumpSS.str() + "\n"
		+ modelAmbientMinSS.str() + "\n";

	int x2 = 0.72*GLOBAL::width;
	int y2 = 0.05*GLOBAL::height;

	Overlay.DrawString(debugOutput.c_str(), x2, y2, COLOR::VioletColor);
}