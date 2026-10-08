#pragma once

#include "../SceneBase.h"

class Player;
namespace UI
{
	class UIManager;
}
namespace Observer
{
	class GoalObserver;
}

class SceneResultTest : public SceneBase
{
public:

	SceneResultTest();
	~SceneResultTest() = default;

	void OnInit() override;

	std::unique_ptr<SceneBase> OnUpdate() override;

private:

	Player* mPlayer;

	UI::UIManager* mUIManager;

	std::unique_ptr<Observer::GoalObserver> mGoalObserver;
};
