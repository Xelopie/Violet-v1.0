#pragma once
#include "stdafx.h"

namespace UPDATE 
{
	void ScanAddress();

	void ReadLocalPlayer();
	bool ReadEntity(int playerId);
	void ReadViewMatrix();
	void ReadBoneMatrix(int playerId, int boneId);
}