#include "Vector3.h"

VECTOR3 VECTOR3::operator-(VECTOR3 vector) {
	return { x - vector.x, y - vector.y, z - vector.z };
}

VECTOR3 VECTOR3::operator+(VECTOR3 vector) {
	return { x + vector.x, y + vector.y, z + vector.z };
}

bool VECTOR3::Zero() {
	return ((x == 0.f) && (y == 0.f) && (z == 0.f));
}
