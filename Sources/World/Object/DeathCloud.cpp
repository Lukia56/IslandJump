#include "DeathCloud.h"
#include "../Component/Collider3D.h"
#include "Collision/Collision3D.h"
#include "Collision/CollisionTag.h"
#include "Observer/Subject.h"
#include "System/TimeManager.h"

namespace
{
	constexpr float kMoveSpeed = 100.0f;

	constexpr Vector3 kBodyCollSize{ 3000.0f, 100.0f, 3000.0f };
}

DeathCloud::DeathCloud(const Vector3& initPos, const Vector3& goalPos) :
	mGoalPos(goalPos),
	mIsTriggered(false),
	mCollider(nullptr)
{
	mTransform->localPosition = initPos;
	mEventSubject = std::make_unique<Observer::Subject>();
}

void DeathCloud::Init()
{
	mCollider = std::make_unique<Collider3D>(
		std::make_unique<Collision::AABB3D>(kBodyCollSize),
		this,
		Collision::Tag::Body
	);
}

void DeathCloud::Update()
{
	mVelocity = Vector3::Zero;

	Vector3 worldPos = mTransform->CalculateWorldPosition();

	if (worldPos.y < mGoalPos.y)
	{
		mVelocity.y = kMoveSpeed * TimeManager::GetDeltaTime();
	}
}

void DeathCloud::PhysicsUpdate()
{
	mTransform->Translate(mVelocity);

	Vector3 worldPos = mTransform->CalculateWorldPosition();
	mCollider->GetShape()->SetPosition(worldPos);
}

void DeathCloud::DebugDraw()
{
	mCollider->GetShape()->DebugDraw();
}

void DeathCloud::ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider)
{
	if (mIsTriggered) return;

	// プレイヤーとの接触時のみ処理を行う
	if (oppCollider->GetOwner()->GetTag() != GameObject::Tag::Player) return;

	mIsTriggered = true;

	mEventSubject->Notify(Observer::Event::FallCloudPlayer);
}
