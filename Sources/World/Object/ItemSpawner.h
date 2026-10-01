#pragma once

#include "../GameObject.h"

class LandTerrainRecorder;
class Collider3D;

/// <summary>
/// プレイヤーに触れたら前に乗っていた地形にアイテムを生成する
/// </summary>
class ItemSpawner : public GameObject
{
public:

	ItemSpawner(Transform* terrain, LandTerrainRecorder* landTerrainRecorder, GameObject* itemRoot);
	~ItemSpawner() = default;

	void Init() override;

	void Update() override;

	void Draw() override;

	void DebugDraw() override;

	void ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider) override;

private:

	bool IsPlayerLandedMyself() const;

private:

	Transform* mTerrain;

	bool mIsTriggered;

	std::unique_ptr<Collider3D> mCollider;

	LandTerrainRecorder* mLandTerrainRecorder;

	GameObject* mItemRoot;
};
