#include "ItemObject.h"
#include <DxLib.h>
#include "../Component/Collider3D.h"
#include "Collision/Collision3D.h"
#include "Collision/CollisionTag.h"
#include "Utility/Color.h"

namespace
{
	constexpr Vector3 kOffsetPos{ 0.0f, 50.0f, 0.0f };

	constexpr float kBodyCollRadius = 20.0f;
}

ItemObject::ItemObject() :
	mCollider(nullptr)
{
}

void ItemObject::Init()
{
	SetTag(Tag::ItemObject);

	mCollider = std::make_unique<Collider3D>(
		std::make_unique<Collision::Sphere3D>(kBodyCollRadius),
		this,
		Collision::Tag::Body
	);
}

void ItemObject::Update()
{
	Vector3 worldPos = mTransform->CalculateWorldPosition();

	mCollider->GetShape()->SetPosition(worldPos);
}

void ItemObject::DebugDraw()
{
	Vector3 pos = mTransform->CalculateWorldPosition();

	DrawSphere3D(pos.GetAsDxLibVector(), 20.0f, 8, Color::magenta.GetAsHexRGB(), Color::magenta.GetAsHexRGB(), true);

	mCollider->GetShape()->DebugDraw();
}

void ItemObject::Setup(const Vector3& spawnPos)
{
	mTransform->localPosition = spawnPos + kOffsetPos;
}
