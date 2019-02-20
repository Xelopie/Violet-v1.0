#pragma once
#include "stdafx.h"

namespace THREAD {
	/* Threads */
	DWORD WINAPI SnapWindow(LPVOID);

	DWORD WINAPI Update(LPVOID);

	DWORD WINAPI Chams(LPVOID);

	DWORD WINAPI Bhop(LPVOID);

	DWORD WINAPI Glow(LPVOID);

	DWORD WINAPI Radar(LPVOID);

	DWORD WINAPI Aimbot(LPVOID);

	DWORD WINAPI FOV(LPVOID);

	DWORD WINAPI CountPlayer(LPVOID);
}