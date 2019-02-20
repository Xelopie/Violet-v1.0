#include "stdafx.h"

// LocalPlayer
const char* OFFSETS::LocalPlayerSig = "\x8D\x34\x85\x00\x00\x00\x00\x89\x15\x00\x00\x00\x00\x8B\x41\x08\x8B\x48\x04\x83\xF9\xFF";
const char* OFFSETS::LocalPlayerMask = "xxx????xx????xxxxxxxxx";

// EntityList
const char* OFFSETS::EntityListSig = "\xBB\x00\x00\x00\x00\x83\xFF\x01\x0F\x8C\x00\x00\x00\x00\x3B\xF8";
const char* OFFSETS::EntityListMask = "x????xxxxx????xx";

// ViewMatrix
const char* OFFSETS::ViewMatrixSig = "\x0F\x10\x05\x00\x00\x00\x00\x8D\x85\x00\x00\x00\x00\xB9";
const char* OFFSETS::ViewMatrixMask = "xxx????xx????x";

// GlowObjectManager
const char* OFFSETS::GlowObjectManagerSig = "\xA1\x00\x00\x00\x00\xA8\x01\x75\x4B";
const char* OFFSETS::GlowObjectManagerMask = "x????xxxx";

// ClientState
const char* OFFSETS::ClientStateSig = "\xA1\x00\x00\x00\x00\x33\xD2\x6A\x00\x6A\x00\x33\xC9\x89\xB0";
const char* OFFSETS::ClientStateMask = "x????xxxxxxxxxx";

// ClientState_ViewAngle
const char* OFFSETS::ClientStateViewAngleSig = "\xF3\x0F\x11\x80\x00\x00\x00\x00\xD9\x46\x04\xD9\x05";
const char* OFFSETS::ClientStateViewAngleMask = "xxxx????xxxxx";

// ForceJump
const char* OFFSETS::ForceJumpSig = "\x8B\x0D\x00\x00\x00\x00\x8B\xD6\x8B\xC1\x83\xCA\x02";
const char* OFFSETS::ForceJumpMask = "xx????xxxxxxx";

// ModelAmbientMin
const char* OFFSETS::ModelAmbientMinSig = "\xF3\x0F\x10\x0D\x00\x00\x00\x00\xF3\x0F\x11\x4C\x24\x00\x8B\x44\x24\x20\x35\x00\x00\x00\x00\x89\x44\x24\x0C";
const char* OFFSETS::ModelAmbientMinMask = "xxxx????xxxxx?xxxxx????xxxx";