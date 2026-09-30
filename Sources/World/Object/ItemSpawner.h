#pragma once

#include "../GameObject.h"

class ItemSpawner : public GameObject
{
public:

	ItemSpawner(Transform* terrain);
	~ItemSpawner() = default;

	void Init() override;

	void Update() override;

	void Draw() override;

private:

	Transform* mTerrain;

	bool mIsTriggered;
};
