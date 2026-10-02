#pragma once

#include "../GameObject.h"

class Collider3D;

class DeathCloud : public GameObject
{
public:

	DeathCloud(const Vector3& initPos, const Vector3& goalPos);
	~DeathCloud() = default;

	void Init() override;

	void Update() override;

	void PhysicsUpdate() override;

	void DebugDraw() override;

private:

	Vector3 mVelocity;

	Vector3 mGoalPos;

	std::unique_ptr<Collider3D> mCollider;
};
