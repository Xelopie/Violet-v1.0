#include "stdafx.h"

#define FOV 10.0f

bool AIMBOT::status = false;

VECTOR2 AIMBOT::ClampAngle(VECTOR2 ViewAngle) {
	if (ViewAngle.x > 89.0f && ViewAngle.x <= 180.0f)
	{
		ViewAngle.x = 89.0f;
	}
	if (ViewAngle.x > 180.f)
	{
		ViewAngle.x -= 360.f;
	}
	if (ViewAngle.x < -89.0f)
	{
		ViewAngle.x = -89.0f;
	}
	if (ViewAngle.y > 180.f)
	{
		ViewAngle.y -= 360.f;
	}
	if (ViewAngle.y < -180.f)
	{
		ViewAngle.y += 360.f;
	}

	return ViewAngle;
}

float AIMBOT::Get2dDistance(VECTOR2 A, VECTOR2 B) {
	return sqrt(
		powf(A.x - B.x, 2.f) +
		powf(A.y - B.y, 2.f)
	);
}

float AIMBOT::Get3dDistance(VECTOR3 A, VECTOR3 B) {
	return sqrt(
		powf(A.x - B.x, 2.f) +
		powf(A.y - B.y, 2.f) +
		powf(A.z - B.z, 2.f)
	);
}

VECTOR2 AIMBOT::CalcAngle(VECTOR3 vector) {
	VECTOR2 angle;
	VECTOR3 delta = { LocalPlayer.vecOrigin.x - vector.x, LocalPlayer.vecOrigin.y - vector.y, LocalPlayer.vecOrigin.z + LocalPlayer.viewOffset.z - vector.z };
	float hyp = sqrt(delta.x * delta.x + delta.y * delta.y);
	angle.x = atanf(delta.z / hyp) * 57.29578f - LocalPlayer.aimPunchAngle.x * 2;
	angle.y = atanf(delta.y / delta.x) * 57.29578f - LocalPlayer.aimPunchAngle.y * 2;

	if (delta.x >= 0.0)
	{
		angle.y += 180.0f;
	}
	return ClampAngle(angle);
}

float AIMBOT::CalcFOV(VECTOR2 angle) {
	VECTOR2 dest = angle;
	VECTOR2 src = (LocalPlayer.aimPunchAngle + LocalPlayer.viewAngle);
	float fov = Get2dDistance(src, dest);

	if (fov > FOV) {
		fov = Get2dDistance(dest.Normalize(), src.Normalize());
	}
	return fov;
}

void AIMBOT::Tick() {
	if (!(GetKeyState(VK_XBUTTON2) & 0x8000)) return;

	int aimID = 0;
	float aimFOV;
	VECTOR2 aimAngle;

	for (int i = 0; i < GLOBAL::playerCount; i++) {

		if (entities[i].base == NULL) continue;

		if (entities[i].dormant == 1) continue;

		if (entities[i].teamNum == LocalPlayer.teamNum) continue;

		if (entities[i].health < 1) continue;

		if (!(entities[i].spottedByMask & 0x01)) continue;

		if (aimID == 0) {
			aimFOV = CalcFOV(CalcAngle(GLOBAL::boneMatrix[i][8]));
			aimID = i;
		}
		else {
			float newAimFOV = CalcFOV(CalcAngle(GLOBAL::boneMatrix[i][8]));

			if (newAimFOV < aimFOV) {
				aimFOV = newAimFOV;
				aimID = i;
			}
		}
	}

	if (aimID == 0) return;
	aimAngle = CalcAngle(GLOBAL::boneMatrix[aimID][8]);
	GLOBAL::debugInfo = aimID;

	if (CalcFOV(aimAngle) <= FOV) {
		MEMORY::Write(GLOBAL::clientStateViewAngleAddy, aimAngle);
	}
}

void AIMBOT::Draw() {
	float radius = GLOBAL::height * FOV / LocalPlayer.fov;
	Overlay.DrawCircle(GLOBAL::width / 2, GLOBAL::height / 2, radius, 20, COLOR::VioletColor);
}