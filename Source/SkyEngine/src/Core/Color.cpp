#include "Core/Color.h"
Color Color::red(1, 0, 0, 1);
Color Color::green(0, 1, 0, 1);
Color Color::blue(0, 0, 1, 1);
Color Color::black(0, 0, 0, 1);

Color::Color()
{

}

Color::Color(float _r, float _g, float _b, float _a)
{
	r = _r;
	g = _g;
	b = _b;
	a = _a;
	
/*
	uintR = (uint8_t)(r * 255);
	uintG = (uint8_t)(g * 255);
	uintB = (uint8_t)(b * 255);
	uintA = (uint8_t)(a * 255);*/
}

Color::Color(uint32_t c)
{
	float inv = 1.0f / 255.0f;
	int alphaMask = 0xFF000000, redMask = 0xFF0000, greenMask = 0xFF00, blueMask = 0xFF;

	a = ((c & alphaMask) >> 24 ) * inv;
	r = ((c & redMask) >> 16) * inv;
	g = ((c & greenMask) >> 8) * inv;
	b = (c & blueMask) * inv;
}



uint8_t Color::GetUintR() { return (uint8_t)(r * 255); }
uint8_t Color::GetUintG() { return (uint8_t)(g * 255); }
uint8_t Color::GetUintB() { return (uint8_t)(b * 255); }
uint8_t Color::GetUintA() { return (uint8_t)(a * 255); }

/*
int Color::GetUintR() { return (int)(r * 255); }
int Color::GetUintG() { return (int)(g * 255); }
int Color::GetUintB() { return (int)(b * 255); }
int Color::GetUintA() { return (int)(a * 255); }
*/