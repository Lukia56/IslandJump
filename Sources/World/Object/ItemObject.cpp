#include "ItemObject.h"
#include "../Component/Collider3D.h"
#include "../Component/Rendering/BillboardRenderer.h"
#include "Collision/Collision3D.h"
#include "Collision/CollisionTag.h"
#include "System/Resource/ResourceBase.h"

namespace
{
	constexpr Vector3 kOffsetPos{ 0.0f, 100.0f, 0.0f };

	constexpr float kBodyCollRadius = 50.0f;
}

ItemObject::ItemObject() :
	mItemType(ItemType::Invalid),
	mCollider(nullptr),
	mBillboard(nullptr)
{
	mBillboard = std::make_unique<BillboardRenderer>(this, nullptr);
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

void ItemObject::Draw()
{
	mBillboard->Draw();
}

void ItemObject::DebugDraw()
{
	mCollider->GetShape()->DebugDraw();
}

void ItemObject::Setup(const Vector3& spawnPos, std::shared_ptr<Resource::ResourceBase> texture, ItemType itemType)
{
	mTransform->localPosition = spawnPos + kOffsetPos;

	mBillboard->SetResource(texture);

	mItemType = itemType;
}
