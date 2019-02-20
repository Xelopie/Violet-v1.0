#include "Vector2.h"

VECTOR2::VECTOR2() {
	x = 0.f;
	y = 0.f;
}

VECTOR2::VECTOR2(float _x, float _y) {
	x = _x;
	y = _y;
}

VECTOR2::VECTOR2(VECTOR3 vector) {
	x = vector.x;
	y = vector.y;
}

VECTOR2 VECTOR2::operator+(VECTOR2 vector) {
	return { x + vector.x, y + vector.y };
}

VECTOR2 VECTOR2::operator-(VECTOR2 vector) {
	return { x - vector.x, y - vector.y };
}

bool VECTOR2::Zero() {
	return ((x == 0.f) && (y == 0.f));
}

VECTOR2 VECTOR2::Normalize() {
	while (x < 0.f || x > 360.f) {
		if (x < 0.f) {
			x += 360.f;
		}
		if (x > 360.f) {
			x -= 360.f;
		}
	}

	return *this;
}