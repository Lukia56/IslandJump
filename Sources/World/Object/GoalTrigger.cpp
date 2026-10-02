#include "GoalTrigger.h"
#include "../Component/Collider3D.h"
#include "Collision/Collision3D.h"
#include "Collision/CollisionTag.h"
#include "Utility/Color.h"

namespace
{
	constexpr Vector3 kBodyCollSize{ 300.0f, 200.0f, 200.0f };
}

GoalTrigger::GoalTrigger() :
	mIsTriggered(false),
	mCollider(nullptr)
{
}

void GoalTrigger::Init()
{
	mCollider = std::make_unique<Collider3D>(
		std::make_unique<Collision::AABB3D>(kBodyCollSize),
		this,
		Collision::Tag::Body
	);
}

void GoalTrigger::Update()
{
	Vector3 worldPos = mTransform->CalculateWorldPosition();

	mCollider->GetShape()->SetPosition(worldPos);
}

void GoalTrigger::DebugDraw()
{
	Color color = mIsTriggered ? Color::red : Color::yellow;

	mCollider->GetShape()->DebugDraw(color);
}

void GoalTrigger::ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider)
{
	if (mIsTriggered) return;

	// プレイヤーとの接触時のみ処理を行う
	if (oppCollider->GetOwner()->GetTag() != GameObject::Tag::Player) return;

	mIsTriggered = true;
}
