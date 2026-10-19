#include "TestRay.h"
#include <DxLib.h>
#include "Collision/Ray.h"
#include "Collision/CollisionManager.h"
#include "System/Input/Keyboard.h"

namespace
{
	constexpr Vector3 kRayDirection{ 0.0f, -1.0f, 0.0f };
	constexpr float kRayLength = 1000.0f;

	constexpr float kMoveSpeed = 10.0f;
}

TestRay::TestRay()
{
}

void TestRay::Init()
{

}

void TestRay::Update()
{
	Vector3 move = Vector3(
		Keyboard::GetInstance().IsDown(KEY_INPUT_L) - Keyboard::GetInstance().IsDown(KEY_INPUT_J),
		0.0f,
		Keyboard::GetInstance().IsDown(KEY_INPUT_I) - Keyboard::GetInstance().IsDown(KEY_INPUT_K)
	);
	move.y = (Keyboard::GetInstance().IsDown(KEY_INPUT_U) - Keyboard::GetInstance().IsDown(KEY_INPUT_O)) * kMoveSpeed * 0.1f;

	mTransform->Translate(move * kMoveSpeed);
}

void TestRay::DebugDraw()
{
	Collision::Ray ray;
	ray.position = mTransform->CalculateWorldPosition();
	ray.direction = kRayDirection;
	ray.maxDistance = kRayLength;

	auto results = CollisionManager::GetInstance().Raycast(ray);

	DrawLine3D(ray.position.GetAsDxLibVector(), (ray.position + ray.direction * ray.maxDistance).GetAsDxLibVector(), 0xffffff);
	
	if (!results.empty()) DrawLine3D(ray.position.GetAsDxLibVector(), results[0].collidePos.GetAsDxLibVector(), 0xff0000);
}
