#pragma once

#include "../GameObject.h"

class LandTerrainRecorder;
class ItemObjectManager;
class Collider3D;
class EffectAnimator;

/// <summary>
/// プレイヤーに触れたら前に乗っていた地形にアイテムを生成する
/// </summary>
class ItemSpawner : public GameObject
{
public:

	ItemSpawner(Transform* terrain, LandTerrainRecorder* landTerrainRecorder, ItemObjectManager* itemObjectManager);
	~ItemSpawner() = default;

	void Init() override;

	void Update() override;

	void DebugDraw() override;

	void ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider) override;

private:

	bool IsPlayerLandedMyself() const;

private:

	Transform* mTerrain;

	bool mIsTriggered;

	float mEffectTimer;

	std::unique_ptr<Collider3D> mCollider;

	std::unique_ptr<EffectAnimator> mEffectAnimator;

	LandTerrainRecorder* mLandTerrainRecorder;

	ItemObjectManager* mItemObjectManager;
};
