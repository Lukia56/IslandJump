#pragma once

#include "../GameObject.h"

class ItemSpawnerManager : public GameObject
{
public:

	ItemSpawnerManager(GameObject* stageManager);
	~ItemSpawnerManager() = default;

	void Init() override;

	void Update() override;
};
