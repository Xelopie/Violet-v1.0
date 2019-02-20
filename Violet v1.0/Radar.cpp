#include "stdafx.h"

bool RADAR::status = false;

void RADAR::Tick() {
	for (int i = 0; i < GLOBAL::playerCount; i++) {
		if (entities[i].teamNum != LocalPlayer.teamNum) {
			MEMORY::Write(entities[i].base + OFFSETS::m_bSpotted, true);
		}
	}
}