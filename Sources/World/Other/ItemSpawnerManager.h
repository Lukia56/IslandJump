#pragma once

#include "../GameObject.h"

class LandTerrainRecorder;

class ItemSpawnerManager : public GameObject
{
public:

	ItemSpawnerManager(GameObject* stageManager, LandTerrainRecorder* landTerrainRecorder);
	~ItemSpawnerManager() = default;

	void Init() override;

	void Update() override;

private:

	GameObject* mItemRoot;

	GameObject* mSpawnerRoot;
};
