#pragma once

#include "../GameObject.h"

class Collider3D;
namespace Observer
{
	class Subject;
}

/// <summary>
/// 下から迫る死亡判定を持つオブジェクト
/// </summary>
class DeathCloud : public GameObject
{
public:

	DeathCloud(const Vector3& initPos, const Vector3& goalPos);
	~DeathCloud() = default;

	void Init() override;

	void Update() override;

	void PhysicsUpdate() override;

	void Draw() override;

	void DebugDraw() override;

	void ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider) override;

public:

	Observer::Subject* GetEventSubject() const { return mEventSubject.get(); }

private:

	Vector3 mVelocity;

	Vector3 mGoalPos;

	float mResultTransitionTimer;

	bool mIsStartTransitionResult;

	bool mIsTriggered;

	std::unique_ptr<Collider3D> mCollider;

	std::unique_ptr<Observer::Subject> mEventSubject;
};
