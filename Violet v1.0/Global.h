#pragma once
#include "stdafx.h"

/* ------------------ USEFUL BONE ID LIST (CT) ------------------- */
#define CT_HEAD 8
#define CT_NECK 7
#define CT_LEFT_SHOULDER 11 
#define CT_LEFT_ELBOW 12
#define CT_LEFT_WRIST 13
#define CT_RIGHT_SHOULDER 41
#define CT_RIGHT_ELBOW 42
#define CT_RIGHT_WRIST 43
#define CT_WAIST 0
#define CT_LEFT_KNEE 71
#define CT_LEFT_ANKLE 72
#define CT_RIGHT_KNEE 78
#define CT_RIGHT_ANKLE 79

/* ------------------ USEFUL BONE ID LIST (TR) ------------------- */
#define T_HEAD 8
#define T_NECK 7
#define T_LEFT_SHOULDER 11 
#define T_LEFT_ELBOW 12
#define T_LEFT_WRIST 13
#define T_RIGHT_SHOULDER 39
#define T_RIGHT_ELBOW 40
#define T_RIGHT_WRIST 41
#define T_WAIST 0
#define T_LEFT_KNEE 67
#define T_LEFT_ANKLE 68
#define T_RIGHT_KNEE 74
#define T_RIGHT_ANKLE 75

struct SMODULE {
	DWORD base;
	DWORD size;
};

struct GLOWOBJECT
{
	/* New Struct */
	DWORD dwBase;
	float r;
	float g;
	float b;
	float a;
	char m_unk[4];
	float m_flUnk;
	float m_flBloomAmount;
	float m_flUnk1;
	bool m_bRenderWhenOccluded;
	bool m_bRenderWhenUnoccluded;
	bool m_bFullBloom;
	char m_unk1;
	int m_nFullBloomStencilTestValue;
	int m_nGlowStyle;
	int m_nSplitScreenSlot;
	int m_nNextFreeSlot;
};



/* ---- Global variables ---- */
namespace GLOBAL {

	extern int playerCount;

	extern float viewMatrix[4][4];

	extern VECTOR3 boneMatrix[32][128];

	extern float debugInfo;

	extern RECT rect;

	extern HWND tWnd;
	extern HWND lWnd;

	extern MSG message;

	extern int width;
	extern int height;

	extern SMODULE clientDLL;
	extern SMODULE engineDLL;

	/* ---- Global constants ---- */

	extern const int bonesUsed;

	extern const int ctBoneId[];
	extern const int trBoneId[];

	extern const char processName[];
	extern const char clientName[];
	extern const char engineName[];

	extern const char tWindowName[];
	extern const char* lWindowName;

	extern const MARGINS margin;

	// Address to be scanned
	extern DWORD entityListAddy;
	extern DWORD localPlayerAddy;
	extern DWORD viewMatrixAddy;
	extern DWORD glowObjectManagerAddy;
	extern DWORD clientStateAddy;
	extern DWORD clientStateViewAngleAddy;
	extern DWORD forceJumpAddy;
	extern DWORD modelAmbientMinAddy;
}







