#pragma once
#include "stdafx.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dwmapi.lib")
#pragma warning( disable : 4996 )

class OVERLAY {

private:
	/* Global variables for overlay */
	IDirect3D9Ex* pObject;
	IDirect3DDevice9Ex* pDevice;
	D3DPRESENT_PARAMETERS Params;
	ID3DXFont* pFont;
	ID3DXFont* pFontCentre;
	ID3DXLine* pLine;

public:
	/* Overlay initializer */
	bool OverlayInit(HWND hWnd);

	/* Declare drawing functions */
	void DrawString(LPCSTR str, float x, float y, D3DCOLOR color);
	void DrawStringCentre(LPCSTR str, float x, float y, D3DCOLOR color);
	void DrawFilledRectangle(float x, float y, float w, float h, D3DCOLOR color);
	void DrawBorderBox(float x, float y, float w, float h, float t, D3DCOLOR color);
	void DrawLine(float x1, float y1, float x2, float y2, D3DCOLOR color);
	void DrawCircle(float x, float y, float r, int numSides, D3DCOLOR color);

	/* Render */
	void Render();


};

extern OVERLAY Overlay;