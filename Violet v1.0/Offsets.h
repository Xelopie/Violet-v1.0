#pragma once
#include "stdafx.h"

struct OFFSETS {
	/* Netvars */
	static const DWORD m_bDormant = 0xED;
	static const DWORD m_iTeamNum = 0xF4;
	static const DWORD m_vecOrigin = 0x138;
	static const DWORD m_iHealth = 0x100;
	static const DWORD m_dwBoneMatrix = 0x26A8;
	static const DWORD m_aimPunchAngle = 0x302C;
	static const DWORD m_clrRender = 0x70;
	static const DWORD m_fFlags = 0x104;
	static const DWORD m_bSpotted = 0x93D;
	static const DWORD dwObjectCount = 0x4;
	static const DWORD m_vecViewOffset = 0x108;
	static const DWORD m_bSpottedByMask = 0x980;
	static const DWORD m_viewAngles = 0x31D8;
	static const DWORD m_iFOV = 0x31E4;
	static const DWORD m_iFOVStart = 0x31E8;
	static const DWORD m_iObserverMode = 0x3374;

	// LocalPlayer
	static const char* LocalPlayerSig;
	static const char* LocalPlayerMask;
	static const int LocalPlayerOffset = 0x3;
	static const int LocalPlayerExtra = 0x4;

	// EntityList
	static const char* EntityListSig;
	static const char* EntityListMask;
	static const int EntityListOffset = 0x1;
	static const int EntityListExtra = 0x0;

	// ViewMatrix
	static const char* ViewMatrixSig;
	static const char* ViewMatrixMask;
	static const int ViewMatrixOffset = 0x3;
	static const int ViewMatrixExtra = 0xB0;

	// GlowObjectManager
	static const char* GlowObjectManagerSig;
	static const char* GlowObjectManagerMask;
	static const int GlowObjectManagerOffset = 0x1;
	static const int GlowObjectManagerExtra = 0x4;

	// ClientState
	static const char* ClientStateSig;
	static const char* ClientStateMask;
	static const int ClientStateOffset = 0x1;
	static const int ClientStateExtra = 0x0;

	// ClientState_ViewAngle
	static const char* ClientStateViewAngleSig;
	static const char* ClientStateViewAngleMask;
	static const int ClientStateViewAngleOffset = 0x4;
	static const int ClientStateViewAngleExtra = 0x0;

	// ForceJump
	static const char* ForceJumpSig;
	static const char* ForceJumpMask;
	static const int ForceJumpOffset = 0x2;
	static const int ForceJumpExtra = 0;

	// Model Ambient 
	static const char* ModelAmbientMinSig;
	static const char* ModelAmbientMinMask;
	static const int ModelAmbientMinOffset = 0x4;
	static const int ModelAmbientMinExtra = 0x0;

};