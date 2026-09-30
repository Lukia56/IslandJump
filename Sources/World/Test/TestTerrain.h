#pragma once

#include "../GameObject.h"
#include <memory>
#include "Utility/Vector.h"

class Collider3D;

class TestTerrain : public GameObject
{
public:

	TestTerrain(const Vector3& size);
	~TestTerrain() = default;

	void Init() override;

	void Update() override;

	void DebugDraw() override;

private:

	std::unique_ptr<Collider3D> mCollider;
};
