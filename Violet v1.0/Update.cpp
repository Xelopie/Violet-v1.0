#include "stdafx.h"

bool DataCompare(const BYTE* data, const BYTE* sig, const char* mask) {
	for (; *mask; ++data, ++sig, ++mask) {
		if (*mask == 'x' && *data != *sig) {
			return false;
		}
	}
	return (*mask == NULL);
}

DWORD FindPattern(DWORD start, DWORD size, const char* sig, const char* mask) {
	BYTE* data = new BYTE[size];

	SIZE_T bytesRead;
	if (!ReadProcessMemory(MEMORY::hProcess, (LPVOID)start, data, size, &bytesRead)) {
		delete[] data;
		return NULL;
	}

	for (DWORD i = 0; i < size; i++) {
		if (DataCompare((const BYTE*)(data + i), (const BYTE*)sig, mask)) {
			delete[] data;
			return start + i;
		}
	}		
	delete[] data;
	return NULL;
}

void UPDATE::ScanAddress() {
	/* Scan for the pattern */
	DWORD tempLocalPlayer = FindPattern(GLOBAL::clientDLL.base, GLOBAL::clientDLL.size, OFFSETS::LocalPlayerSig, OFFSETS::LocalPlayerMask);
	DWORD tempEntityList = FindPattern(GLOBAL::clientDLL.base, GLOBAL::clientDLL.size, OFFSETS::EntityListSig, OFFSETS::EntityListMask);
	DWORD tempViewMatrix = FindPattern(GLOBAL::clientDLL.base, GLOBAL::clientDLL.size, OFFSETS::ViewMatrixSig, OFFSETS::ViewMatrixMask);
	DWORD tempGlowObjectManager = FindPattern(GLOBAL::clientDLL.base, GLOBAL::clientDLL.size, OFFSETS::GlowObjectManagerSig, OFFSETS::GlowObjectManagerMask);
	DWORD tempClientState = FindPattern(GLOBAL::engineDLL.base, GLOBAL::engineDLL.size, OFFSETS::ClientStateSig, OFFSETS::ClientStateMask);
	DWORD tempClientStateViewAngle = FindPattern(GLOBAL::engineDLL.base, GLOBAL::engineDLL.size, OFFSETS::ClientStateViewAngleSig, OFFSETS::ClientStateViewAngleMask);
	DWORD tempForceJump = FindPattern(GLOBAL::clientDLL.base, GLOBAL::clientDLL.size, OFFSETS::ForceJumpSig, OFFSETS::ForceJumpMask);
	DWORD tempModelAmbientMin = FindPattern(GLOBAL::engineDLL.base, GLOBAL::engineDLL.size, OFFSETS::ModelAmbientMinSig, OFFSETS::ModelAmbientMinMask);

	/* Add the sig offsets */
	tempLocalPlayer += OFFSETS::LocalPlayerOffset;
	tempEntityList += OFFSETS::EntityListOffset;
	tempViewMatrix += OFFSETS::ViewMatrixOffset;
	tempGlowObjectManager += OFFSETS::GlowObjectManagerOffset;
	tempClientState += OFFSETS::ClientStateOffset;
	tempClientStateViewAngle += OFFSETS::ClientStateViewAngleOffset;
	tempForceJump += OFFSETS::ForceJumpOffset;
	tempModelAmbientMin += OFFSETS::ModelAmbientMinOffset;

	/* Dereference the pointer */
	tempLocalPlayer = MEMORY::Read<DWORD>(tempLocalPlayer);
	tempEntityList = MEMORY::Read<DWORD>(tempEntityList);
	tempViewMatrix = MEMORY::Read<DWORD>(tempViewMatrix);
	tempGlowObjectManager = MEMORY::Read<DWORD>(tempGlowObjectManager);
	tempClientState = MEMORY::Read<DWORD>(tempClientState);
	tempClientStateViewAngle = MEMORY::Read<DWORD>(tempClientStateViewAngle);
	tempForceJump = MEMORY::Read<DWORD>(tempForceJump);
	tempModelAmbientMin = MEMORY::Read<DWORD>(tempModelAmbientMin);

	/* Add the extra */
	GLOBAL::localPlayerAddy = tempLocalPlayer + OFFSETS::LocalPlayerExtra;
	GLOBAL::entityListAddy = tempEntityList + OFFSETS::EntityListExtra;
	GLOBAL::viewMatrixAddy = tempViewMatrix + OFFSETS::ViewMatrixExtra;
	GLOBAL::glowObjectManagerAddy = tempGlowObjectManager + OFFSETS::GlowObjectManagerExtra;
	GLOBAL::clientStateAddy = tempClientState + OFFSETS::ClientStateExtra;
	GLOBAL::forceJumpAddy = tempForceJump + OFFSETS::ForceJumpExtra;
	GLOBAL::modelAmbientMinAddy = tempModelAmbientMin + OFFSETS::ModelAmbientMinExtra;
	GLOBAL::clientStateViewAngleAddy = MEMORY::Read<DWORD>(GLOBAL::clientStateAddy) + tempClientStateViewAngle + OFFSETS::ClientStateViewAngleExtra;

}

/* Read process for view matrix */
void UPDATE::ReadViewMatrix() {
	MEMORY::ReadSize(GLOBAL::viewMatrixAddy, &GLOBAL::viewMatrix);
}

/* Read process for local player */
void UPDATE::ReadLocalPlayer()
{
	MEMORY::ReadSize(GLOBAL::localPlayerAddy, &LocalPlayer.base);
	MEMORY::ReadSize(LocalPlayer.base + OFFSETS::m_iTeamNum, &LocalPlayer.teamNum);
	MEMORY::ReadSize(LocalPlayer.base + OFFSETS::m_vecOrigin, &LocalPlayer.vecOrigin);
	MEMORY::ReadSize(LocalPlayer.base + OFFSETS::m_aimPunchAngle, &LocalPlayer.aimPunchAngle);
	MEMORY::ReadSize(LocalPlayer.base + OFFSETS::m_fFlags, &LocalPlayer.flag);
	MEMORY::ReadSize(LocalPlayer.base + OFFSETS::m_vecViewOffset, &LocalPlayer.viewOffset);
	MEMORY::ReadSize(LocalPlayer.base + OFFSETS::m_viewAngles, &LocalPlayer.viewAngle);
	if (MEMORY::Read<DWORD>(LocalPlayer.base + OFFSETS::m_iFOV) == 0) {
		LocalPlayer.fov = MEMORY::Read<DWORD>(LocalPlayer.base + OFFSETS::m_iFOVStart);
	}
	else {
		LocalPlayer.fov = MEMORY::Read<DWORD>(LocalPlayer.base + OFFSETS::m_iFOV);
	}
}

/* Read process for bone matrix */
void UPDATE::ReadBoneMatrix(int playerId, int boneId)
{
	DWORD boneMatrixBase = MEMORY::Read<DWORD>(entities[playerId].base + OFFSETS::m_dwBoneMatrix);
	MEMORY::ReadSize(boneMatrixBase + 0x30 * boneId + 0x0C, &GLOBAL::boneMatrix[playerId][boneId].x);
	MEMORY::ReadSize(boneMatrixBase + 0x30 * boneId + 0x1C, &GLOBAL::boneMatrix[playerId][boneId].y);
	MEMORY::ReadSize(boneMatrixBase + 0x30 * boneId + 0x2C, &GLOBAL::boneMatrix[playerId][boneId].z);
}

/* Read process for entities */
bool UPDATE::ReadEntity(int playerId) {
	MEMORY::ReadSize(GLOBAL::entityListAddy + playerId * 0x10, &entities[playerId].base);

	if (entities[playerId].base == NULL) return false; // Check if there is any player to return

	MEMORY::ReadSize(entities[playerId].base + OFFSETS::m_bDormant, &entities[playerId].dormant);
	MEMORY::ReadSize(entities[playerId].base + OFFSETS::m_iTeamNum, &entities[playerId].teamNum);
	MEMORY::ReadSize(entities[playerId].base + OFFSETS::m_iHealth, &entities[playerId].health);
	MEMORY::ReadSize(entities[playerId].base + OFFSETS::m_vecOrigin, &entities[playerId].vecOrigin);
	MEMORY::ReadSize(entities[playerId].base + OFFSETS::m_bSpotted, &entities[playerId].spotted);
	MEMORY::ReadSize(entities[playerId].base + OFFSETS::m_bSpottedByMask, &entities[playerId].spottedByMask);

	return true;
}


