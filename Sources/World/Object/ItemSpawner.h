#pragma once

#include "../GameObject.h"

class Collider3D;

class ItemSpawner : public GameObject
{
public:

	ItemSpawner(Transform* terrain);
	~ItemSpawner() = default;

	void Init() override;

	void Update() override;

	void Draw() override;

	void DebugDraw() override;

	void ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider) override;

private:

	Transform* mTerrain;

	bool mIsTriggered;

	std::unique_ptr<Collider3D> mCollider;
};
