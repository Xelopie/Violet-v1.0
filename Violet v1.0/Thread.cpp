#include "stdafx.h"

DWORD WINAPI THREAD::SnapWindow(LPVOID)
{
	/* Infinite thread of snapping overlay to target window */
	while (true)
	{
		GLOBAL::tWnd = FindWindow(0, GLOBAL::tWindowName);
		/* Check the tWnd value */
		if (GLOBAL::tWnd)
		{
			/* If target window is not on top */
			if (GLOBAL::tWnd != GetForegroundWindow()) {
				ShowWindow(GLOBAL::lWnd, SW_HIDE);
			}
			else ShowWindow(GLOBAL::lWnd, SW_SHOWNOACTIVATE);

			/* If the tWnd value is non-null */
			GetWindowRect(GLOBAL::tWnd, &GLOBAL::rect);
			GLOBAL::width = GLOBAL::rect.right - GLOBAL::rect.left;
			GLOBAL::height = GLOBAL::rect.bottom - GLOBAL::rect.top;

			/* Get the window's style */
			DWORD dwStyle = GetWindowLong(GLOBAL::tWnd, GWL_STYLE);

			/* Check if there is a border for the target window */
			if (dwStyle & WS_BORDER)
			{
				GLOBAL::rect.top += 23;
				GLOBAL::height -= 23;
			}
			MoveWindow(GLOBAL::lWnd, GLOBAL::rect.left, GLOBAL::rect.top, GLOBAL::width, GLOBAL::height, true);	// Move the overlay to target window and resize it
		}
		else
		{
			/* Else send the error msg */
			char errorMsg[125];
			sprintf(errorMsg, "Make sure %s is running!", GLOBAL::tWindowName);
			MessageBox(0, errorMsg, "Error - Cannot find the game!", MB_OK | MB_ICONERROR);
			exit(1);
		}
		Sleep(10);
	}
}

DWORD WINAPI THREAD::Update(LPVOID) {
	while (true) {
		/* Read our information */
		UPDATE::ReadLocalPlayer();

		/* Read the viewMatrix */
		UPDATE::ReadViewMatrix();

		/* Read the boneMatrix */
		for (int i = 0; i < GLOBAL::playerCount; i++) {
			if (entities[i].teamNum == 2) {
				for (int j = 0; j < GLOBAL::bonesUsed; j++) {
					UPDATE::ReadBoneMatrix(i, GLOBAL::trBoneId[j]);
				}
			}
			else if (entities[i].teamNum == 3) {
				for (int j = 0; j < GLOBAL::bonesUsed; j++) {
					UPDATE::ReadBoneMatrix(i, GLOBAL::ctBoneId[j]);
				}
			}
		}

		/* Update entities' data */
		for (int i = 0; i < 32; i++) {
			UPDATE::ReadEntity(i);
		}
		Sleep(1);
	}
}

DWORD WINAPI THREAD::Chams(LPVOID) {
	while (true) {
		CHAMS::Tick();
		Sleep(10);
	}
}

DWORD WINAPI THREAD::Bhop(LPVOID) {
	while (true) {
		BHOP::Tick();
		Sleep(1);
	}
}

DWORD WINAPI THREAD::Glow(LPVOID) {
	while (true) {
		GLOW::Tick();
		Sleep(1);
	}
}

DWORD WINAPI THREAD::Radar(LPVOID) {
	while (true) {
		RADAR::Tick();
		Sleep(5);
	}
}

DWORD WINAPI THREAD::Aimbot(LPVOID) {
	while (true) {
		AIMBOT::Tick();
		Sleep(1);
	}
}

DWORD WINAPI THREAD::FOV(LPVOID) {
	for(int i = 0; i < 1000; i++) {
		FOV::Start();
		Sleep(1);
	}
	return 0;
}

DWORD WINAPI THREAD::CountPlayer(LPVOID) {
	while (true) {
		int playerCount = 0;
		for (int i = 0; i < 64; i++) {
			if (UPDATE::ReadEntity(i)) {
				playerCount++;
			}
		}
		GLOBAL::playerCount = playerCount+1;
		Sleep(5000);
	}
}