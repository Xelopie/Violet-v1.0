#pragma once
#include "Vector3.h"

struct VECTOR2
{
	float x;
	float y;

	VECTOR2();

	VECTOR2(float _x, float _y);

	VECTOR2(VECTOR3 vector);

	VECTOR2 operator+(VECTOR2 vector);

	VECTOR2 operator-(VECTOR2 vector);

	bool Zero();

	VECTOR2 Normalize();
};