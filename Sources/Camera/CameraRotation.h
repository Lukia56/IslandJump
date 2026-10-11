#pragma once

#include "ICamera.h"

class CameraRotation : public ICamera
{
public:

	CameraRotation(const Vector3& pos, const Vector3& rotateSpeed);
	~CameraRotation() = default;

	void Update(Camera::View& view) override;

private:

	Vector3 mPosition;

	Vector3 mRotation;

	Vector3 mRotateSpeed;
};
