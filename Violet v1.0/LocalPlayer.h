#pragma once
#include "stdafx.h"

struct LOCALPLAYER {
	DWORD base;
	DWORD teamNum;
	VECTOR2 aimPunchAngle;
	VECTOR3 vecOrigin;
	DWORD flag;
	VECTOR3 viewOffset;
	VECTOR2 viewAngle;
	DWORD fov;
};

extern LOCALPLAYER LocalPlayer;