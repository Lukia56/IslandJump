#pragma once

#include "ICamera.h"

class Transform;

class CameraRotation : public ICamera
{
public:

	CameraRotation(Transform* targetTransform, const Vector3& rotateSpeed, float distance);
	~CameraRotation() = default;

	void Setup() override;

	void Update(Camera::View& view) override;

private:

	Transform* mTargetTransform;

	Vector3 mPosition;

	Vector3 mRotation;

	Vector3 mRotateSpeed;

	float mDistance;
};
