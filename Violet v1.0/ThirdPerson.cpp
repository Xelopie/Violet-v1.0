#include "stdafx.h"

bool THIRDPERSON::status = false;

void THIRDPERSON::Start() {
	MEMORY::Write(LocalPlayer.base + OFFSETS::m_iObserverMode, 1);
}

void THIRDPERSON::End() {
	MEMORY::Write(LocalPlayer.base + OFFSETS::m_iObserverMode, 0);
}