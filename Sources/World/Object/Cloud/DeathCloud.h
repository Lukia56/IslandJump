#pragma once

#include "World/GameObject.h"

class Collider3D;
namespace Observer
{
	class Subject;
}
namespace Resource
{
	class ResourceBase;
}

/// <summary>
/// 下から迫る死亡判定を持つオブジェクト
/// </summary>
class DeathCloud : public GameObject
{
public:

	DeathCloud(const Vector3& initPos, const Vector3& goalPos, float moveSpeed, std::shared_ptr<Resource::ResourceBase> model);
	~DeathCloud() = default;

	void Init() override;

	void Update() override;

	void PhysicsUpdate() override;

	void DebugDraw() override;

	void ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider) override;

public:

	Observer::Subject* GetEventSubject() const { return mEventSubject.get(); }

	void SetDoMove(bool flag) { mDoMove = flag; }

private:

	Vector3 mVelocity;

	Vector3 mGoalPos;

	float mMoveSpeed;

	float mResultTransitionTimer;

	bool mIsStartTransitionResult;

	bool mDoMove;

	bool mIsTriggered;

	std::unique_ptr<Collider3D> mCollider;

	std::unique_ptr<Observer::Subject> mEventSubject;
};
