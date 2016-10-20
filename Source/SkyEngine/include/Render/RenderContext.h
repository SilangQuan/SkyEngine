#pragma once

class RenderContext
{

public:
	RenderContext() {};

	Vector3 viewPos;
	Matrix4x4 modelMatrix;
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
	Matrix4x4 viewProjectionMatrix;
};