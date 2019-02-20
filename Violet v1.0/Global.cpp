#include "stdafx.h"

int GLOBAL::playerCount = 0;

float GLOBAL::viewMatrix[4][4];

VECTOR3 GLOBAL::boneMatrix[32][128];

float GLOBAL::debugInfo;

RECT GLOBAL::rect;

HWND GLOBAL::tWnd;
HWND GLOBAL::lWnd;

MSG GLOBAL::message;

int GLOBAL::width = GetSystemMetrics(SM_CXSCREEN);
int GLOBAL::height = GetSystemMetrics(SM_CYSCREEN);

SMODULE GLOBAL::clientDLL;
SMODULE GLOBAL::engineDLL;

/* ---- Global constants ---- */

const int GLOBAL::bonesUsed = 13;
const int GLOBAL::ctBoneId[] = { 8, 7, 11, 12, 13, 41, 42, 43, 0, 71, 72, 78, 79 };
const int GLOBAL::trBoneId[] = { 8, 7, 11, 12, 13, 39, 40, 41, 0, 67, 68, 74, 75 };

const char GLOBAL::processName[] = "csgo.exe";
const char GLOBAL::clientName[] = "client_panorama.dll";
const char GLOBAL::engineName[] = "engine.dll";

const char GLOBAL::tWindowName[] = "Counter-Strike: Global Offensive";
const char* GLOBAL::lWindowName;

const MARGINS GLOBAL::margin = { -1 };

// Address to be scanned
DWORD GLOBAL::entityListAddy;
DWORD GLOBAL::localPlayerAddy;
DWORD GLOBAL::viewMatrixAddy;
DWORD GLOBAL::glowObjectManagerAddy;
DWORD GLOBAL::clientStateAddy;
DWORD GLOBAL::clientStateViewAngleAddy;
DWORD GLOBAL::forceJumpAddy;
DWORD GLOBAL::modelAmbientMinAddy;