#pragma once
#include "stdafx.h"

struct ENTITY {
	DWORD teamNum;
	DWORD base;
	bool dormant;
	int health;
	VECTOR3 vecOrigin;
	bool spotted;
	bool spottedByMask;
	DWORD modelIndex;
};

extern ENTITY entities[32];