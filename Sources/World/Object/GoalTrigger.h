#pragma once

#include "../GameObject.h"

class Collider3D;
namespace Observer
{
	class Subject;
}

/// <summary>
/// ゴール判定を行い、イベントを送信する
/// </summary>
class GoalTrigger : public GameObject
{
public:

	GoalTrigger();
	~GoalTrigger() = default;

	void Init() override;

	void Update() override;

	void DebugDraw() override;

	void ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider) override;

public:

	Observer::Subject* GetEventSubject() const { return mEventSubject.get(); }

private:

	bool mIsTriggered;

	std::unique_ptr<Collider3D> mCollider;

	std::unique_ptr<Observer::Subject> mEventSubject;
};
