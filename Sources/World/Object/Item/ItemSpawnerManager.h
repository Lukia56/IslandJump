#pragma once

#include "World/GameObject.h"

class PlayerLandRecorder;
class ItemObjectManager;

/// <summary>
/// アイテムスポナーを生成する
/// </summary>
class ItemSpawnerManager : public GameObject
{
public:

	ItemSpawnerManager(GameObject* stageManager, PlayerLandRecorder* landTerrainRecorder, ItemObjectManager* itemObjectManager, int itemNum);
	~ItemSpawnerManager() = default;

	void Init() override;

	void Update() override;

private:

	GameObject* mSpawnerRoot;
};
