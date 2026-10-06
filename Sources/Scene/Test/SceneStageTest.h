#pragma once

#include "../SceneBase.h"

class Player;
class Skybox;

class SceneStageTest : public SceneBase
{
public:

	SceneStageTest();
	~SceneStageTest() = default;

	void OnInit() override;

	std::unique_ptr<SceneBase> OnUpdate() override;

private:

	Player* mPlayer;

	Skybox* mSkybox;
};
