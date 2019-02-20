#pragma once

struct VECTOR3
{
	float x;
	float y;
	float z;

	VECTOR3 operator-(VECTOR3 vector);

	VECTOR3 operator+(VECTOR3 vector);

	bool Zero();
};