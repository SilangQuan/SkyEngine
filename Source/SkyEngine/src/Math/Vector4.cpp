#include "Math/Vector4.h"

void Vector4::set(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _x;
	z = _x;
	w = _x;
}

Vector4 Vector4::operator+(const Vector4 &v) const
{
	return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
}

Vector4 Vector4::operator-(const Vector4 &v) const
{
	return Vector4(x - v.x, y - v.y, z - v.z, w- v.w);
}