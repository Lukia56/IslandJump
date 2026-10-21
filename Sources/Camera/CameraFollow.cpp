#include "CameraFollow.h"
#include <imgui.h>
#include "System/InputManager.h"
#include "System/Input/Mouse.h"
#include "Utility/Math.h"
#include "World/Component/Transform.h"

namespace
{
	constexpr Vector3 kInitRot{ 0.0f, Math::kPi, 0.0f };

	constexpr float kDistance = 700.0f;

	constexpr float kMaxPitch = 70.0f;
	constexpr float kMinPitch = -80.0f;

	constexpr float kMoveViewLatency = 0.25f;

	constexpr Vector2 kMouseSensitivity{ 0.1f, 0.15f };

	constexpr float kGamepadLookSpeed = 2.0f;
	constexpr Vector2 kGamepadSensitivity{ 1.0f, 1.0f };
}

CameraFollow::CameraFollow(Transform* target) :
	mEyePosition(Vector3::Zero),
	mRotation(kInitRot),
	mTargetRotation(kInitRot),
	mTarget(target)
{
}

void CameraFollow::Update(Camera::View& view)
{
	// 視点を移動する
	Vector2 viewMoveDir = Mouse::GetInstance().GetRelativePos();
	if (viewMoveDir != Vector2::Zero)
	{
		viewMoveDir.x *= kMouseSensitivity.x;
		viewMoveDir.y *= kMouseSensitivity.y;
		mTargetRotation += Vector3(viewMoveDir.y, viewMoveDir.x, 0.0f) * Math::ToRadian(1.0f);
	}
	else
	{
		Vector3 look = InputManager::GetInstance().GetAsVector3(Input::Action::Look);
		look.x *= kGamepadSensitivity.x;
		look.y *= kGamepadSensitivity.y;
		mTargetRotation += look * kGamepadLookSpeed * Math::ToRadian(1.0f);
	}

	// ピッチを制限する
	mTargetRotation.x = Math::Clamp(mTargetRotation.x, Math::ToRadian(kMinPitch), Math::ToRadian(kMaxPitch));

	mRotation = mRotation.Lerp(mTargetRotation, kMoveViewLatency);

	Vector3 targetPos = mTarget->CalculateWorldPosition();

	float yawSinParam = std::sin(mRotation.y);
	float yawCosParam = std::cos(mRotation.y);
	float pitchSinParam = std::sin(mRotation.x);
	float pitchCosParam = std::cos(mRotation.x);

	// 回転させたカメラの座標を計算
	Vector3 rotatedOffsetPos;
	rotatedOffsetPos.x = pitchCosParam * yawSinParam * kDistance;
	rotatedOffsetPos.y = pitchSinParam * kDistance;
	rotatedOffsetPos.z = pitchCosParam * yawCosParam * kDistance;

	mEyePosition = targetPos - rotatedOffsetPos;

	view.eyePosition = mEyePosition;
	view.targetPosition = targetPos;
}

void CameraFollow::DebugDraw()
{
	if (ImGui::Begin("Camera"))
	{
		float eyePosPtr[] = { mEyePosition.x, mEyePosition.y, mEyePosition.z };
		ImGui::InputFloat3("EyePosition", eyePosPtr, "%.1f");

		Vector3 targetPos = mTarget->CalculateWorldPosition();
		float targetPosPtr[] = { targetPos.x, targetPos.y, targetPos.z };
		ImGui::InputFloat3("TargetPosition", targetPosPtr, "%.1f");

		float rotPtr[] = { Math::ToDegree(mRotation.x), Math::ToDegree(mRotation.y), Math::ToDegree(mRotation.z) };
		ImGui::InputFloat3("Rotation", rotPtr, "%.1f");

		ImGui::End();
	}
}
