#include "DeathCloud.h"
#include "CloudModel.h"
#include "../Component/Collider3D.h"
#include "Collision/Collision3D.h"
#include "Collision/CollisionTag.h"
#include "Observer/Subject.h"
#include "System/TimeManager.h"
#include "System/Resource/ResourceBase.h"

namespace
{
	constexpr Vector3 kBodyCollSize{ 3000.0f, 100.0f, 3000.0f };

	constexpr float kResultTransitionTime = 1.0f;

	constexpr int kCloudXNum = 5;
	constexpr int kCloudZNum = 15;

	constexpr float kCloudXSpace = 1000.0f;
	constexpr float kCloudZSpace = 400.0f;

	constexpr float kCloudYOffset = -200.0f;
}

DeathCloud::DeathCloud(const Vector3& initPos, const Vector3& goalPos, float moveSpeed, std::shared_ptr<Resource::ResourceBase> model) :
	mGoalPos(goalPos),
	mMoveSpeed(moveSpeed),
	mResultTransitionTimer(0.0f),
	mIsStartTransitionResult(false),
	mDoMove(true),
	mIsTriggered(false),
	mCollider(nullptr)
{
	mTransform->localPosition = initPos;
	mEventSubject = std::make_unique<Observer::Subject>();

	for (int i = 0; i < kCloudZNum; i++)
	{
		for (int j = 0; j < kCloudXNum; j++)
		{
			CloudModel* cloud = CreateToChild<CloudModel>(model);
			cloud->GetTransform()->localPosition = Vector3(kCloudXSpace * j - kCloudXSpace * kCloudXNum * 0.5f, kCloudYOffset, kCloudZSpace * i - kCloudZSpace * kCloudZNum * 0.5f);
		}
	}
}

void DeathCloud::Init()
{
	mCollider = std::make_unique<Collider3D>(
		std::make_unique<Collision::AABB3D>(kBodyCollSize),
		this,
		Collision::Tag::Body,
		true,
		false
	);
}

void DeathCloud::Update()
{
	mVelocity = Vector3::Zero;

	Vector3 worldPos = mTransform->CalculateWorldPosition();

	if (worldPos.y < mGoalPos.y && mDoMove)
	{
		mVelocity.y = mMoveSpeed * TimeManager::GetDeltaTime();
	}

	if (mIsTriggered && !mIsStartTransitionResult)
	{
		mResultTransitionTimer -= TimeManager::GetDeltaTime();

		if (mResultTransitionTimer < 0.0f)
		{
			mEventSubject->Notify(Observer::Event::TransitionResult);

			mIsStartTransitionResult = true;
		}
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

	mResultTransitionTimer = kResultTransitionTime;

	mEventSubject->Notify(Observer::Event::FallCloudPlayer);
}
