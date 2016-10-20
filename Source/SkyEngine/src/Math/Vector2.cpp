#include "Math/Vector2.h"
Vector2::Vector2()
{
	x = y = 0.0f;
}

Vector2::Vector2(float _x, float _y) :x(_x), y(_y)
{
}


Vector2::~Vector2()
{
	//dtor
}

void Vector2::set(float _x, float _y)
{
	x = _x;
	y = _y;
}

float Vector2::magnitude() const
{

	return sqrt(x*x + y*y);

}

float Vector2::sqrtMagnitude() const
{
	return x*x + y*y;
}

Vector2 operator * (const Vector2& lhs, double rhs)
{
	return Vector2(rhs*lhs.x, rhs*lhs.y);
}

Vector2 operator * (double lhs, const Vector2& rhs)
{
	return Vector2(lhs*rhs.x, lhs*rhs.y);

}

Vector2 Vector2::operator+(const Vector2 &v) const
{
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2 &v) const
{
	return Vector2(x - v.x, y - v.y);
}