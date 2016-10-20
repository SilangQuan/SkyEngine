#include "Core/Camera.h"

Camera::Camera(const Vector3& _pos, const Vector3& _target, const Vector3& _up)
{
	transform.position = _pos;
	transform.rotation = Quaternion::identity;
	transform.scale = Vector3::one;
	target = target;
	up = _up;
	viewMatrix = Transform::LookAt(_pos, target, _up);
}

Camera::Camera()
{
	transform.position = Vector3(0,0,-5);
	transform.rotation = Quaternion::identity;
	transform.scale = Vector3::one;
	target = Vector3::zero;
	up = Vector3::up;
	viewMatrix = Transform::LookAt(transform.position, target, up);
}

//Only for perspective camera
Camera::Camera(const Vector3& _pos, float fov, float aspect, float _zNear, float _zFar)
{
	transform.position = _pos;
	transform.rotation = Quaternion::identity;
	transform.scale = Vector3::one;
	up = Vector3::up;
	target = Vector3::zero;
	viewMatrix = Transform::LookAt(transform.position, target, up);
	zNear = _zNear;
	zFar = _zFar;

	projectionMaxtrix = Transform::Perspective(fov, aspect, _zNear, _zFar);
}


Camera::~Camera()
{

}

void Camera::SetFrustrum(float left, float right, float bottom, float top, float nearValue, float farValue, bool perspective)
{
	isPerspective = perspective;
	if (perspective)
	{
		projectionMaxtrix = Transform::Frustum(left, right, bottom, top, nearValue, farValue);
	}
	else
	{
		projectionMaxtrix = Transform::OrthoFrustum(left, right, bottom, top, nearValue, farValue);
	}
}

Matrix4x4 Camera::GetViewMatrix()
{
	//return Transform::LookAt(transform.position, target, up);
	return Transform::FPSView(transform.position, transform.rotation);
}

Matrix4x4 Camera::GetProjectionMatrix()
{
	return projectionMaxtrix;
}



