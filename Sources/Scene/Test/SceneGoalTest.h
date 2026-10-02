#pragma once

#include "../SceneBase.h"

class Player;
namespace UI
{
	class UIManager;
}
namespace Observer
{
	class ShowGoalUI;
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

	std::unique_ptr<Observer::ShowGoalUI> mShowGoalUI;
};
