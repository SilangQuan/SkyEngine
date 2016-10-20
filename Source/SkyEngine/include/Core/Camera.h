#pragma once
#include "Base.h"
class Renderer;

class Camera
{
public: 
	Camera();
	Camera(const Vector3& pos, const Vector3& target, const Vector3& up);
	Camera(const Vector3& _pos, float fov, float aspect, float near, float far);
	~Camera();

	void SetFrustrum(float left, float right, float bottom, float top, float nearValue, float farValue, bool perspective);
	Matrix4x4 GetViewMatrix();
	Matrix4x4 GetProjectionMatrix();
	Vector3 target;
	Vector3 up;
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMaxtrix;
	Transform transform;

	bool isPerspective;
	float fov;
	float aspect;
	float zNear;
	float zFar;
};