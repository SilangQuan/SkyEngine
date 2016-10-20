#pragma once
#include <cmath>
#include <cfloat>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "Matrix.h"
#include "Random.h"

class Mathf
{
public:
	Mathf() {}
	~Mathf() {}

	static float Pi;
	static float Rad2Deg;
	static float Deg2Rad;
	static float Infinity;
	static float NegativeInfinity;
	static float EPSILON; 
	static float Clamp(float x, float min, float max)
	{
		return fmin(max, fmax(x, min));
	}

	static float Max(float a, float b)
	{
		return fmax(a, b);
	}

	static inline float Lerp(float a, float b, float t)
	{
		return a + (b - a) * t;
	}

	static float Sin(float angle)
	{
		return sin(angle);
	}

	static float Cos(float angle)
	{
		return cos(angle);
	}
};



