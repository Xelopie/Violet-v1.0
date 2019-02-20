#include "stdafx.h"

LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
		/* Start to render */
		Overlay.Render();
		break;

	case WM_CREATE:
		/* Adjust the margin */
		DwmExtendFrameIntoClientArea(hWnd, &GLOBAL::margin);
		break;

	case WM_DESTROY:
		/* Quit the overlay */
		PostQuitMessage(1);
		return 0;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hSecInstance, LPSTR nCmdLine, INT nCmdShow) {
	/* Generate a random name for the overlay */
	GLOBAL::lWindowName = RANDOMNAME::Generator();

	/* Create handles */
	HANDLE hCountPlayer = NULL;
	HANDLE hSnapWindow = NULL;
	HANDLE hUpdate = NULL;
	HANDLE hChams = NULL;
	HANDLE hBhop = NULL;
	HANDLE hGlow = NULL;
	HANDLE hRadar = NULL;
	HANDLE hAimbot = NULL;
	HANDLE hFOV = NULL;

	/* Create a WNDCLASSEX */
	WNDCLASSEX wClass; // Create a WNDCLASSEXX

	/* Set the WNDCLASSEX parameter for later use */
	wClass.cbClsExtra = NULL;
	wClass.cbSize = sizeof(WNDCLASSEX);
	wClass.cbWndExtra = NULL;
	wClass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	wClass.hCursor = LoadCursor(0, IDC_ARROW);
	wClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	wClass.hIconSm = LoadIcon(0, IDI_APPLICATION);
	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = WinProc;
	wClass.lpszClassName = GLOBAL::lWindowName;
	wClass.lpszMenuName = GLOBAL::lWindowName;
	wClass.style = CS_VREDRAW | CS_HREDRAW;

	/* If RegisterClassEx fails, exit */
	if (!RegisterClassEx(&wClass))
		exit(1);

	/* Set tWnd to the handle of "tWindowName" */
	GLOBAL::tWnd = FindWindow(0, GLOBAL::tWindowName);

	/* Create the window and display it */
	if (GLOBAL::tWnd)
	{
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

		GLOBAL::lWnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED, GLOBAL::lWindowName, GLOBAL::lWindowName, WS_POPUP, 1, 1, GLOBAL::width, GLOBAL::height, 0, 0, 0, 0);
		SetLayeredWindowAttributes(GLOBAL::lWnd, 0, 1.0f, LWA_ALPHA);	// Set the window with the alpha value
		SetLayeredWindowAttributes(GLOBAL::lWnd, 0, RGB(0, 0, 0), LWA_COLORKEY);	// Set the window with the colorkey value
		ShowWindow(GLOBAL::lWnd, SW_SHOW);	// Display the window
	}

	/* Attach, GetModule and ScanAddress */
	MEMORY::Attach(GLOBAL::processName, PROCESS_ALL_ACCESS);
	GLOBAL::clientDLL = MEMORY::GetModule(GLOBAL::clientName);
	GLOBAL::engineDLL = MEMORY::GetModule(GLOBAL::engineName);
	UPDATE::ScanAddress();

	/* Create threads **/
	hSnapWindow = CreateThread(NULL, NULL, &THREAD::SnapWindow, NULL, NULL, NULL);
	hCountPlayer = CreateThread(NULL, NULL, &THREAD::CountPlayer, NULL, NULL, NULL);
	hUpdate = CreateThread(NULL, NULL, &THREAD::Update, NULL, NULL, NULL);

	/* Initialize overlay */
	Overlay.OverlayInit(GLOBAL::lWnd);

	/* Infinite loop */
	while (!GetAsyncKeyState(VK_F10))
	{
		/* If there is a message on the message list */
		if (PeekMessage(&GLOBAL::message, GLOBAL::lWnd, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&GLOBAL::message); // Dispatch and sent the message to WinProc function
			TranslateMessage(&GLOBAL::message); // Translate the virtual-key press into character input
		}

		if (GetAsyncKeyState(VK_F1)) {
			ESP::status = !ESP::status;
			Sleep(250);
		}

		if (GetAsyncKeyState(VK_F2)) {
			RECOILCROSSHAIR::status = !RECOILCROSSHAIR::status;
			Sleep(250);
		}

		if (GetAsyncKeyState(VK_F3)) {
			CHAMS::status = !CHAMS::status;
			if (CHAMS::status) {
				hChams = CreateThread(NULL, NULL, &THREAD::Chams, NULL, NULL, NULL);
			}
			else {
				TerminateThread(hChams, 0);
				CloseHandle(hChams);
				CHAMS::End();
			}
			Sleep(250);
		}

		if (GetAsyncKeyState(VK_F4)) {
			BHOP::status = !BHOP::status;
			if (BHOP::status) {
				hBhop = CreateThread(0, 0, &THREAD::Bhop, NULL, NULL, NULL);
			}
			else {
				TerminateThread(hBhop, 0);
				CloseHandle(hBhop);
			}
			Sleep(250);
		}

		if (GetAsyncKeyState(VK_F5)) {
			GLOW::status = !GLOW::status;
			if (GLOW::status) {
				hGlow = CreateThread(0, 0, &THREAD::Glow, 0, 0, 0);
			}
			else {
				TerminateThread(hGlow, 0);
				CloseHandle(hGlow);
			}
			Sleep(250);
		}

		if (GetAsyncKeyState(VK_F6)) {
			RADAR::status = !RADAR::status;
			if (RADAR::status) {
				hRadar = CreateThread(0, 0, &THREAD::Radar, 0, 0, 0);
			}
			else {
				TerminateThread(hRadar, 0);
				CloseHandle(hRadar);
			}
			Sleep(250);
		}

		if (GetAsyncKeyState(VK_F7)) {
			AIMBOT::status = !AIMBOT::status;
			if (AIMBOT::status) {
				hAimbot = CreateThread(0, 0, &THREAD::Aimbot, 0, 0, 0);
			}
			else {
				TerminateThread(hAimbot, 0);
				CloseHandle(hAimbot);
			}
			Sleep(250);
		}

		if (GetAsyncKeyState(VK_F8)) {
			hFOV = CreateThread(0, 0, &THREAD::FOV, 0, 0, 0);
			
			Sleep(250);
		}
		
		if (GetAsyncKeyState(VK_F9)) {
			THIRDPERSON::status = !THIRDPERSON::status;
			if (THIRDPERSON::status) {
				THIRDPERSON::Start();
			}
			else {
				THIRDPERSON::End();
			}
			Sleep(250);
		}

		if (GetAsyncKeyState(VK_PRIOR)) {
			FOV::targetFOV += 10;
			Sleep(250);
		}

		if (GetAsyncKeyState(VK_NEXT)) {
			FOV::targetFOV -= 10;
			Sleep(250);
		}
	}

	delete GLOBAL::lWindowName;
}