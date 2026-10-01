#include "ItemSpawner.h"
#include <DxLib.h>
#include "Collision/Collision3D.h"
#include "Utility/Color.h"
#include "World/Component/Collider3D.h"

namespace
{
	constexpr float kTriggerRadius = 25.0f;
}

ItemSpawner::ItemSpawner(Transform* terrain) :
	mTerrain(terrain),
	mIsTriggered(false),
	mCollider(nullptr)
{
}

void ItemSpawner::Init()
{
	SetTag(Tag::ItemSpawner);

	mTransform->localPosition = mTerrain->CalculateWorldPosition();
	mTransform->Translate(0.0f, 50.0f, 0.0f);

	mCollider = std::make_unique<Collider3D>(
		std::make_unique<Collision::Sphere3D>(kTriggerRadius),
		this,
		Collision::Tag::Sensor
	);
}

void ItemSpawner::Update()
{
	Vector3 worldPos = mTransform->CalculateWorldPosition();

	mCollider->GetShape()->SetPosition(worldPos);
}

void ItemSpawner::Draw()
{
	Vector3 pos = mTransform->CalculateWorldPosition();

	int color = mIsTriggered ? Color::green.GetAsHexRGB() : Color::red.GetAsHexRGB();

	DrawSphere3D(pos.GetAsDxLibVector(), 25.0f, 8, color, color, true);
}

void ItemSpawner::DebugDraw()
{
	mCollider->GetShape()->DebugDraw();
}

void ItemSpawner::ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider)
{
	if (oppCollider->GetOwner()->GetTag() != GameObject::Tag::Player) return;

	mIsTriggered = true;

	mCollider->Disable();
}
