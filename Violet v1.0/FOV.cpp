#include "stdafx.h"

int FOV::targetFOV = 90;

void FOV::Start() {
	//if (targetFOV != LocalPlayer.fov) {
	//	MEMORY::Write(LocalPlayer.base + OFFSETS::m_iFOV, targetFOV);
	//}
	MEMORY::Write(LocalPlayer.base + OFFSETS::m_iFOV, targetFOV);
}