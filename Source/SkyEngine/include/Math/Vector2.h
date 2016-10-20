#pragma once
#include <math.h>
#include <assert.h>
#include <iostream>

#define PI 3.14159265
using namespace std;

class Vector2
{
public:
	float x;
	float y;
	Vector2();
	Vector2(float x, float y);
	~Vector2();
	friend Vector2 operator * (const Vector2& lhs, double rhs);
	friend Vector2 operator * (double lhs, const Vector2& rhs);
	//Add two Vectors
	Vector2 operator+(const Vector2 &v) const;
	//Subtracts one vector from another
	Vector2 operator-(const Vector2 &v) const;


	float magnitude() const;
	float sqrtMagnitude() const;
	void set(float _x, float _y);
};