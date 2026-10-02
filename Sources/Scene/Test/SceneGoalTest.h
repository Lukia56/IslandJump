#pragma once

#include "../SceneBase.h"

class Player;
namespace UI
{
	class UIManager;
}

class SceneGoalTest : public SceneBase
{
public:

	SceneGoalTest();
	~SceneGoalTest() = default;

	void OnInit() override;

	std::unique_ptr<SceneBase> OnUpdate() override;

private:

	Player* mPlayer;

	UI::UIManager* mUIManager;
};
