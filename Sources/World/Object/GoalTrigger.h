#pragma once

#include "../GameObject.h"

class Collider3D;
namespace UI
{
	class UIManager;
}

class GoalTrigger : public GameObject
{
public:

	GoalTrigger();
	~GoalTrigger() = default;

	void Init() override;

	void Update() override;

	void DebugDraw() override;

	void ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider) override;

private:

	bool mIsTriggered;

	std::unique_ptr<Collider3D> mCollider;
};
