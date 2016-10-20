#pragma once
#include "Math/Mathf.h"
#include <assert.h>
#include <iostream>
#include <stdint.h>

#define PI 3.14159265
using namespace std;

class Color
{
private:


public: 
	float r;
	float g;
	float b;
	float a;
/*
	uint8_t uintR;
	uint8_t uintG;
	uint8_t uintB;
	uint8_t uintA;*/
	static Color red;
	static Color green;
	static Color blue;
	static Color black;
	Color();
	Color(uint32_t c);
	Color(float r, float g, float b, float a);
	uint8_t GetUintR();
	uint8_t GetUintG();
	uint8_t GetUintB();
	uint8_t GetUintA();

	uint32_t inline GetUintValue()
	{
		return (uint8_t)(a * 255) << 24 | (uint8_t)(r * 255) << 16 | (uint8_t)(g * 255) << 8 | (uint8_t)(b * 255) << 0;
		//c.GetUintA() << 24) | (c.GetUintR << 16) | (c.GetUintG << 8) | (c.GetUintB << 0);
	}

	friend std::ostream& operator<<(std::ostream& output, const Color& color)
	{
		output << "(" << color.r << "," << color.g << "," << color.b << ")" << "\n";
		return output;
	}

	static inline Color Lerp(const Color& start, const Color& end, float t)
	{
		float r = Mathf::Lerp(start.r, end.r, t);
		float g = Mathf::Lerp(start.g, end.g, t);
		float b = Mathf::Lerp(start.b, end.b, t);
		float a = Mathf::Lerp(start.a, end.a, t);
		return Color(r, g, b, a);
	}
};

