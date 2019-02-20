#include "stdafx.h"

bool BHOP::status = false;

void BHOP::Tick() {
	if (!(GetAsyncKeyState(VK_SPACE) & 0x8000)) return;

	if (LocalPlayer.flag == 257 || LocalPlayer.flag == 263) {
		MEMORY::WriteSize(GLOBAL::forceJumpAddy, true);
	}
	else if (LocalPlayer.flag == 256 || LocalPlayer.flag == 262) {
		MEMORY::WriteSize(GLOBAL::forceJumpAddy, false);
	}
}