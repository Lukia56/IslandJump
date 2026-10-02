#pragma once

#include "../SceneBase.h"

class Player;

class SceneDeathCloudTest : public SceneBase
{
public:

	SceneDeathCloudTest();
	~SceneDeathCloudTest() = default;

	void OnInit() override;

	std::unique_ptr<SceneBase> OnUpdate() override;

private:

	Player* mPlayer;
};
