#include "stdafx.h"

//const DWORD model_ambient_min = 0x58ED1C;

bool CHAMS::status = false;

void CHAMS::Tick()
{
	for (int i = 1; i < GLOBAL::playerCount; i++)
	{
		struct {
			BYTE r;
			BYTE g;
			BYTE b;
		} color;

		if (entities[i].teamNum != LocalPlayer.teamNum) { // Chams on enemies only
			color = { 255, 0, 255 };
			MEMORY::WriteSize(entities[i].base + OFFSETS::m_clrRender, color);
		}
		else if (entities[i].teamNum == LocalPlayer.teamNum) { // Disable chams on teammates
			color = { 255, 255, 255 };
			MEMORY::WriteSize(entities[i].base + OFFSETS::m_clrRender, color);
		}
	}
	float brightness = 10.f;
	DWORD thisPtr = GLOBAL::modelAmbientMinAddy - 0x2C;
	DWORD xored = *(DWORD*)&brightness ^ thisPtr;
	MEMORY::Write(GLOBAL::modelAmbientMinAddy, xored);
}

void CHAMS::End() {
	for (int i = 1; i < GLOBAL::playerCount; i++)
	{
		struct {
			BYTE r;
			BYTE g;
			BYTE b;
		} color;

		if (entities[i].teamNum != LocalPlayer.teamNum) { // Chams on enemies only
			color = { 255, 255, 255 };
			MEMORY::WriteSize(entities[i].base + OFFSETS::m_clrRender, color);
		}
		else if (entities[i].teamNum == LocalPlayer.teamNum) { // Disable chams on teammates
			color = { 255, 255, 255 };
			MEMORY::WriteSize(entities[i].base + OFFSETS::m_clrRender, color);
		}
	}
	float brightness = 0.f;
	DWORD thisPtr = GLOBAL::modelAmbientMinAddy - 0x2C;
	DWORD xored = *(DWORD*)&brightness ^ thisPtr;
	MEMORY::Write(GLOBAL::modelAmbientMinAddy, xored);
}