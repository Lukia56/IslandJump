#pragma once

#include "../GameObject.h"

class LandTerrainRecorder;
class ItemObjectManager;

/// <summary>
/// アイテムスポナーを生成する
/// </summary>
class ItemSpawnerManager : public GameObject
{
public:

	ItemSpawnerManager(GameObject* stageManager, LandTerrainRecorder* landTerrainRecorder, ItemObjectManager* itemObjectManager, int itemNum);
	~ItemSpawnerManager() = default;

	void Init() override;

	void Update() override;

private:

	GameObject* mSpawnerRoot;
};
