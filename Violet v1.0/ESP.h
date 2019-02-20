#pragma once
#include "stdafx.h"

namespace ESP {
	extern bool status;

	float Get3dDistance(VECTOR3 coorA, VECTOR3 coorB);
	bool WorldToScreen(VECTOR3& from, VECTOR3& to, float vM[4][4], RECT m_Rect);

	void ConnectBones(int bone1, int bone2);
	void Draw();
}