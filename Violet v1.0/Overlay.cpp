#include "stdafx.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dwmapi.lib")

#define PI 3.14159265

bool OVERLAY::OverlayInit(HWND hWnd)
{
	/* If D3D create function fails */
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &pObject))) {
		exit(1);
	}

	/* Clear the p_Params */
	ZeroMemory(&Params, sizeof(Params));

	/* Setup the p_Params */
	Params.Windowed = TRUE;
	Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	Params.hDeviceWindow = hWnd;
	Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	Params.BackBufferFormat = D3DFMT_A8R8G8B8;
	Params.BackBufferWidth = GLOBAL::width;
	Params.BackBufferHeight = GLOBAL::height;
	Params.EnableAutoDepthStencil = TRUE;
	Params.AutoDepthStencilFormat = D3DFMT_D16;

	/* If CreateDeviceEx function fails */
	if (FAILED(pObject->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &Params, 0, &pDevice))) {
		exit(1);
	}

	return 0;
}

void OVERLAY::DrawLine(float x1, float y1, float x2, float y2, D3DCOLOR color)
{
	D3DXVECTOR2 vectorList[2] = { { x1, y1 }, { x2, y2 } };
	pLine->Begin();
	pLine->Draw(vectorList, 2, color);
	pLine->End();
}

void OVERLAY::DrawString(LPCSTR str, float x, float y, D3DCOLOR color)
{
	RECT fontPos;
	fontPos.left = x;
	fontPos.top = y;
	pFont->DrawTextA(0, str, strlen(str), &fontPos, DT_NOCLIP, color);
}

void OVERLAY::DrawStringCentre(LPCSTR str, float x, float y, D3DCOLOR color)
{
	RECT fontPos;
	fontPos.left = x - 100;
	fontPos.top = y - 100;
	fontPos.right = x + 100;
	fontPos.bottom = y + 100;
	pFontCentre->DrawTextA(0, str, strlen(str), &fontPos, DT_CENTER | DT_VCENTER, color);
}

void OVERLAY::DrawFilledRectangle(float x, float y, float w, float h, D3DCOLOR color)
{
	D3DRECT rect = { x, y, x + w, y + h };
	pDevice->Clear(1, &rect, D3DCLEAR_TARGET, color, 0, 0);
}

void OVERLAY::DrawBorderBox(float x, float y, float w, float h, float t, D3DCOLOR color)
{
	DrawFilledRectangle(x, y, w - t, t, color); // Top horizontal
	DrawFilledRectangle(x + t, y + h - t, w - t, t, color); // Bottom horizontal
	DrawFilledRectangle(x, y + t, t, h - t, color); // Left vertical
	DrawFilledRectangle(x + w - t, y, t, h - t, color); // Right vertical
}

void OVERLAY::DrawCircle(float x, float y, float r, int numSides, D3DCOLOR Color)
{
	D3DXVECTOR2 Line[128];
	float Step = PI * 2.0 / numSides;
	int Count = 0;
	for (float a = 0; a < PI*2.0; a += Step)
	{
		float X1 = r * cos(a) + x;
		float Y1 = r * sin(a) + y;
		float X2 = r * cos(a + Step) + x;
		float Y2 = r * sin(a + Step) + y;
		Line[Count].x = X1;
		Line[Count].y = Y1;
		Line[Count + 1].x = X2;
		Line[Count + 1].y = Y2;
		Count += 2;
	}
	pLine->Begin();
	pLine->Draw(Line, Count, Color);
	pLine->End();
}

void OVERLAY::Render()
{
	if (GLOBAL::tWnd == GetForegroundWindow())
	{
		HWND hWnd = FindWindow(NULL, GLOBAL::tWindowName);
		if (hWnd == NULL) {
			return;
		}

		pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
		D3DXCreateFont(pDevice, 15, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &pFont);
		D3DXCreateFont(pDevice, 12, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &pFontCentre);
		D3DXCreateLine(pDevice, &pLine);

		pDevice->BeginScene();

		/* Print status */
		INFOSTATUS::Print();

		/* When ESPBox is enabled */	
		if (ESP::status) {
			ESP::Draw();
		}

		/* When recoilcrosshair is on */
		if (RECOILCROSSHAIR::status) {
			RECOILCROSSHAIR::Draw();
		}

		/* When aimbot is on */
		if (AIMBOT::status) {
			AIMBOT::Draw();
		}

		/* End scene and present it */
		pDevice->EndScene();
		pDevice->PresentEx(0, 0, 0, 0, 0);

		/* Release the resources */
		pLine->Release();
		pFont->Release();
		pFontCentre->Release();
		return;
	}
}

OVERLAY Overlay;

