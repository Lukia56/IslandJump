#include "CameraRotation.h"
#include "System/TimeManager.h"
#include "Utility/Math.h"

CameraRotation::CameraRotation(const Vector3& pos, const Vector3& rotateSpeed) :
	mPosition(pos)
{
	mRotateSpeed.x = Math::ToRadian(rotateSpeed.x);
	mRotateSpeed.y = Math::ToRadian(rotateSpeed.y);
	mRotateSpeed.z = Math::ToRadian(rotateSpeed.z);
}

void CameraRotation::Update(Camera::View& view)
{
	float pitchRad = mRotation.x;
	float yawRad = mRotation.y;

	Vector3 forward;
	forward.x = std::cos(pitchRad) * std::sin(yawRad);
	forward.y = std::sin(pitchRad);
	forward.z = std::cos(pitchRad) * std::cos(yawRad);

	view.eyePosition = mPosition;
	view.targetPosition = mPosition + forward;

	mRotation += mRotateSpeed * TimeManager::GetDeltaTime();
}
