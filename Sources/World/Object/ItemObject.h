#pragma once

#include "../GameObject.h"

/// <summary>
/// プレイヤーが取得できる配置されたアイテム
/// </summary>
class ItemObject : public GameObject
{
public:

	ItemObject(const Vector3& spawnPos);
	~ItemObject() = default;

	void Init() override;

	void Update() override;

	void DebugDraw() override;

private:

	Vector3 mSpawnPos;
};
