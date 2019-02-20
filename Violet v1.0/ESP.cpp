#include "stdafx.h"
#define PI 3.141592653f

bool ESP::status = false;

VECTOR3 BoneCoor[128];

/* 3D distance calculator */
float ESP::Get3dDistance(VECTOR3 coorA, VECTOR3 coorB) {
	return sqrt(
		powf(coorA.x - coorB.x, 2.f) +
		powf(coorA.y - coorB.y, 2.f) +
		powf(coorA.z - coorB.z, 2.f)
	);
}

/* World to screen matrix */
bool ESP::WorldToScreen(VECTOR3& from, VECTOR3& to, float vM[4][4], RECT m_Rect)
{
	float w = 0.0f;

	to.x = vM[0][0] * from.x + vM[0][1] * from.y + vM[0][2] * from.z + vM[0][3];
	to.y = vM[1][0] * from.x + vM[1][1] * from.y + vM[1][2] * from.z + vM[1][3];
	w = vM[3][0] * from.x + vM[3][1] * from.y + vM[3][2] * from.z + vM[3][3];

	/* w-value for debug */
	to.z = w;

	if (w < 0.01f)
		return false;

	float invw = 1.0f / w;
	to.x *= invw;
	to.y *= invw;

	int width = (int)(m_Rect.right - m_Rect.left);
	int height = (int)(m_Rect.bottom - m_Rect.top);

	float x = width / 2;
	float y = height / 2;

	x += 0.5 * to.x * width + 0.5;
	y -= 0.5 * to.y * height + 0.5;

	to.x = x;
	to.y = y;

	return true;
}

void ESP::ConnectBones(int bone1, int bone2) {
	float boneX1 = BoneCoor[bone1].x;
	float boneY1 = BoneCoor[bone1].y;
	float boneX2 = BoneCoor[bone2].x;
	float boneY2 = BoneCoor[bone2].y;
	Overlay.DrawLine(boneX1, boneY1, boneX2, boneY2, COLOR::VioletColor);
}

void ESP::Draw() {

	for (int i = 0; i < GLOBAL::playerCount; i++)
	{
		if (entities[i].base == NULL) continue;

		if (entities[i].health < 1) continue;

		if (entities[i].dormant == 1) continue;

		if (entities[i].teamNum == LocalPlayer.teamNum) continue;

		VECTOR3 enemyHeadCoor = {};
		VECTOR3 enemyFootCoor = {};

		VECTOR3 enemyHeadOrigin = { entities[i].vecOrigin.x, entities[i].vecOrigin.y, entities[i].vecOrigin.z + 75.0f };
		VECTOR3 enemyFootOrigin = { entities[i].vecOrigin.x, entities[i].vecOrigin.y, entities[i].vecOrigin.z - 10.0f };

		if (WorldToScreen(enemyFootOrigin, enemyFootCoor, GLOBAL::viewMatrix, GLOBAL::rect) && WorldToScreen(enemyHeadOrigin, enemyHeadCoor, GLOBAL::viewMatrix, GLOBAL::rect)) {

			float& topX = enemyHeadCoor.x;
			float& topY = enemyHeadCoor.y;
			float& bottomX = enemyFootCoor.x;
			float& bottomY = enemyFootCoor.y;

			// ESP RECTANGLE
			float height = bottomY - topY;
			float width = height * (45.0f / 75.0f);
			float leftX = bottomX - width / 2.0f;
			float rightX = bottomX + width / 2.0f;
			Overlay.DrawBorderBox(leftX, topY, width, height, 1, COLOR::VioletColor);

			// ESP LINE
			Overlay.DrawLine(bottomX, bottomY, (GLOBAL::width) / 2, GLOBAL::height, COLOR::BlackColor);

			// ESP DISTANCE
			float distance = Get3dDistance(LocalPlayer.vecOrigin, entities[i].vecOrigin);
			string distanceString = to_string((int)(distance / 100.0f)) + "m";
			float stringY = topY - (bottomY - topY) / 7.0f;
			float stringX = bottomX;
			Overlay.DrawStringCentre(distanceString.c_str(), stringX, stringY, COLOR::RedColor);

			// ESP HEALTH BAR
			float healthPercent = (float)entities[i].health / 100.0f;
			float healthBarLength = healthPercent * (float)height;
			float healthBarY = (float)bottomY - healthPercent * (float)height;
			Overlay.DrawFilledRectangle(leftX - 4.f, healthBarY, 1.f, healthBarLength, COLOR::GreenColor);

			//// ESP BONES
			//if (entities[i].teamNum == 3) 	// TeamNum == CT
			//{
			//	for (int j = 0; j < GLOBAL::bonesUsed; j++) {
			//		VECTOR3 boneOrigin = GLOBAL::boneMatrix[i][GLOBAL::ctBoneId[j]];
			//		WorldToScreen(boneOrigin, BoneCoor[GLOBAL::ctBoneId[j]], GLOBAL::viewMatrix, GLOBAL::rect);
			//	}

			//	/* Connect the bones HARD-CODE WARNING!!!!!!!!!!!!!!!!!! */
			//	ConnectBones(GLOBAL::ctBoneId[0], GLOBAL::ctBoneId[1]);
			//	ConnectBones(GLOBAL::ctBoneId[1], GLOBAL::ctBoneId[2]);
			//	ConnectBones(GLOBAL::ctBoneId[2], GLOBAL::ctBoneId[3]);
			//	ConnectBones(GLOBAL::ctBoneId[3], GLOBAL::ctBoneId[4]);
			//	ConnectBones(GLOBAL::ctBoneId[1], GLOBAL::ctBoneId[5]);
			//	ConnectBones(GLOBAL::ctBoneId[5], GLOBAL::ctBoneId[6]);
			//	ConnectBones(GLOBAL::ctBoneId[6], GLOBAL::ctBoneId[7]);
			//	ConnectBones(GLOBAL::ctBoneId[1], GLOBAL::ctBoneId[8]);
			//	ConnectBones(GLOBAL::ctBoneId[8], GLOBAL::ctBoneId[9]);
			//	ConnectBones(GLOBAL::ctBoneId[9], GLOBAL::ctBoneId[10]);
			//	ConnectBones(GLOBAL::ctBoneId[8], GLOBAL::ctBoneId[11]);
			//	ConnectBones(GLOBAL::ctBoneId[11], GLOBAL::ctBoneId[12]);

			//}
			//else if (entities[i].teamNum == 2) 	// TeamNum == T
			//{
			//	for (int j = 0; j < GLOBAL::bonesUsed; j++) {
			//		VECTOR3 boneOrigin = GLOBAL::boneMatrix[i][GLOBAL::trBoneId[j]];
			//		WorldToScreen(boneOrigin, BoneCoor[GLOBAL::trBoneId[j]], GLOBAL::viewMatrix, GLOBAL::rect);
			//	}

			//	/* Connect the bones HARD-CODE WARNING!!!!!!!!!!!!!!!!!! */
			//	ConnectBones(GLOBAL::trBoneId[0], GLOBAL::trBoneId[1]);
			//	ConnectBones(GLOBAL::trBoneId[1], GLOBAL::trBoneId[2]);
			//	ConnectBones(GLOBAL::trBoneId[2], GLOBAL::trBoneId[3]);
			//	ConnectBones(GLOBAL::trBoneId[3], GLOBAL::trBoneId[4]);
			//	ConnectBones(GLOBAL::trBoneId[1], GLOBAL::trBoneId[5]);
			//	ConnectBones(GLOBAL::trBoneId[5], GLOBAL::trBoneId[6]);
			//	ConnectBones(GLOBAL::trBoneId[6], GLOBAL::trBoneId[7]);
			//	ConnectBones(GLOBAL::trBoneId[1], GLOBAL::trBoneId[8]);
			//	ConnectBones(GLOBAL::trBoneId[8], GLOBAL::trBoneId[9]);
			//	ConnectBones(GLOBAL::trBoneId[9], GLOBAL::trBoneId[10]);
			//	ConnectBones(GLOBAL::trBoneId[8], GLOBAL::trBoneId[11]);
			//	ConnectBones(GLOBAL::trBoneId[11], GLOBAL::trBoneId[12]);
			//}

			//// ESP HEAD
			//float radius = (bottomY - topY) / 15.0f;
			//if (WorldToScreen(GLOBAL::boneMatrix[i][8], BoneCoor[8], GLOBAL::viewMatrix, GLOBAL::rect)) 
			//	Overlay.DrawCircle(BoneCoor[8].x, BoneCoor[8].y, radius, 20, COLOR::VioletColor);
		}
	}
}

