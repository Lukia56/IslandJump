#pragma once

#include "../GameObject.h"

class Collider3D;
namespace Collision
{
	class IShape3D;
}

class TestCollider : public GameObject
{
public:

	TestCollider(std::unique_ptr<Collision::IShape3D> shape);
	~TestCollider() = default;

	void Init() override;

	void Update() override;

	void DebugDraw() override;

private:

	std::unique_ptr<Collider3D> mCollider;
};
