#include "stdafx.h"

bool GLOW::status = false;

void GLOW::Tick() {
	/* Read the address for glowObjectManager */
	DWORD glowObjectManager = MEMORY::Read<DWORD>(GLOBAL::glowObjectManagerAddy);

	/* Read the number of object */
	int glowObjectCount = MEMORY::Read<int>(GLOBAL::glowObjectManagerAddy + OFFSETS::dwObjectCount);

	/* Glow the players */
	if (glowObjectManager != NULL && glowObjectCount > 0) {
		for (int i = 0; i < GLOBAL::playerCount; i++) {
			for (int n = 0; n < glowObjectCount; n++)
			{
				GLOWOBJECT glowObject = MEMORY::Read<GLOWOBJECT>(glowObjectManager + n * 0x38);
				if (glowObject.dwBase == NULL) {
					continue;
				}

				if (glowObject.dwBase == entities[i].base) //If it's a player
				{
					//if (entities[i].teamNum == GLOBAL::LocalPlayer.teamNum) {
					//	glowObject.r = 0.0f;
					//	glowObject.g = 0.0f;
					//	glowObject.b = 0.0f;
					//	glowObject.a = 1.0f;
					//	glowObject.m_bRenderWhenOccluded = true;
					//	glowObject.m_bRenderWhenUnoccluded = false;
					//	glowObject.m_bFullBloom = false;
					//	glowObject.m_nGlowStyle = 1;
					//}
					if (entities[i].teamNum != LocalPlayer.teamNum) {	// Glow enemies only
						glowObject.r = 255.0f;
						glowObject.g = 0.0f;
						glowObject.b = 255.0f;
						glowObject.a = 1.0f;
						glowObject.m_bRenderWhenOccluded = true;
						glowObject.m_bRenderWhenUnoccluded = false;
						glowObject.m_bFullBloom = false;
						glowObject.m_nGlowStyle = 0;
					}
					MEMORY::Write(glowObjectManager + 0x38 * n, glowObject);
				}
			}
		}
	}

}