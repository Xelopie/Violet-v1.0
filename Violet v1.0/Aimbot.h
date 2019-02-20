#pragma once
#include "stdafx.h"

namespace AIMBOT {
	extern bool status;

	VECTOR2 ClampAngle(VECTOR2 ViewAngle);
	float Get2dDistance(VECTOR2 A, VECTOR2 B);
	float Get3dDistance(VECTOR3 A, VECTOR3 B);

	VECTOR2 CalcAngle(VECTOR3 vector);
	float CalcFOV(VECTOR2 vector);

	void Draw();

	void Tick();
}