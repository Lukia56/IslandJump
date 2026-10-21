#include "CameraRotation.h"
#include "System/TimeManager.h"
#include "Utility/Math.h"
#include "World/Component/Transform.h"

namespace
{
	// 距離が0だとカメラとターゲットの位置が完全に重なってしまうため、0以上にするための値
	constexpr float kMinDistance = 0.1f;

	constexpr float kEyePosLatency = 0.05f;
}

CameraRotation::CameraRotation(Transform* targetTransform, const Vector3& rotateSpeed, float distance) :
	mTargetTransform(targetTransform),
	mDistance(Math::Max(distance, kMinDistance))
{
	mRotateSpeed.x = Math::ToRadian(rotateSpeed.x);
	mRotateSpeed.y = Math::ToRadian(rotateSpeed.y);
	mRotateSpeed.z = Math::ToRadian(rotateSpeed.z);
}

void CameraRotation::Setup()
{
}

void CameraRotation::Update(Camera::View& view)
{
	float pitchRad = mRotation.x;
	float yawRad = mRotation.y;

	Vector3 forward;
	forward.x = std::cos(pitchRad) * std::sin(yawRad);
	forward.y = std::sin(pitchRad);
	forward.z = std::cos(pitchRad) * std::cos(yawRad);

	Vector3 targetPos = mTargetTransform->CalculateWorldPosition();

	view.eyePosition = view.eyePosition.Lerp(targetPos + forward * mDistance, kEyePosLatency);
	view.targetPosition = targetPos;

	mRotation += mRotateSpeed * TimeManager::GetDeltaTime();
}
