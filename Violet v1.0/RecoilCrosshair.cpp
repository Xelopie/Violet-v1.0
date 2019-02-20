#include "stdafx.h"

#define PI 3.14f

bool RECOILCROSSHAIR::status = false;

void RECOILCROSSHAIR::Draw()
{
	float screenWidth = GLOBAL::width;
	float screenHeight = GLOBAL::height;

	float x = screenWidth / 2;
	float y = screenHeight / 2;

	float dx = screenHeight / LocalPlayer.fov;
	float dy = screenHeight / LocalPlayer.fov;

	x -= dx * LocalPlayer.aimPunchAngle.y;
	y += dy * LocalPlayer.aimPunchAngle.x;

	Overlay.DrawLine(x + 10, y, x - 10, y, COLOR::RedColor);
	Overlay.DrawLine(x, y + 10, x, y - 10, COLOR::RedColor);

}