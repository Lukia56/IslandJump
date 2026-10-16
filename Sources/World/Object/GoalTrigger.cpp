#include "GoalTrigger.h"
#include "../Component/Collider3D.h"
#include "Collision/Collision3D.h"
#include "Collision/CollisionTag.h"
#include "Observer/Subject.h"
#include "System/TimeManager.h"
#include "Utility/Color.h"

namespace
{
	constexpr Vector3 kBodyCollSize{ 900.0f, 400.0f, 400.0f };
	constexpr Vector3 kBodyCollOffset{ 0.0f, 200.0f, 0.0f };

	constexpr float kResultTransitionTime = 3.0f;
}

GoalTrigger::GoalTrigger() :
	mResultTransitionTimer(0.0f),
	mIsTriggered(false),
	mCollider(nullptr),
	mEventSubject(nullptr)
{
	mEventSubject = std::make_unique<Observer::Subject>();
}

void GoalTrigger::Init()
{
	mCollider = std::make_unique<Collider3D>(
		std::make_unique<Collision::AABB3D>(kBodyCollSize, kBodyCollOffset),
		this,
		Collision::Tag::Body,
		true,
		false
	);
}

void GoalTrigger::Update()
{
	Vector3 worldPos = mTransform->CalculateWorldPosition();

	mCollider->GetShape()->SetPosition(worldPos);

	if (mIsTriggered)
	{
		mResultTransitionTimer -= TimeManager::GetDeltaTime();

		if (mResultTransitionTimer < 0.0f)
		{
			mEventSubject->Notify(Observer::Event::TransitionResult);

			SetActive(false);
		}
	}
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

	mResultTransitionTimer = kResultTransitionTime;

	mEventSubject->Notify(Observer::Event::ReachGoal);
}
