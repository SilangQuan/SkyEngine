#pragma once
class Vector4
{
public:
	float x, y, z, w;

	Vector4() : x(0), y(0), z(0), w(0) {};
	Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};
	~Vector4() {};

	//Add two Vectors
	Vector4 operator+(const Vector4 &v) const;
	//Subtracts one vector from another
	Vector4 operator-(const Vector4 &v) const;

	void set(float _x, float _y, float _z, float _w);


protected:
private:
};