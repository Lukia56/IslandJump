#pragma once

#include "../SceneBase.h"

class SceneItemSpawnerTest : public SceneBase
{
public:

	SceneItemSpawnerTest();
	~SceneItemSpawnerTest() = default;

	void OnInit() override;

	std::unique_ptr<SceneBase> OnUpdate() override;
};
