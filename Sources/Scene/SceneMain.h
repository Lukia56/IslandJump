#pragma once

#include "SceneBase.h"

class Player;
class Skybox;
namespace UI
{
	class UIManager;
}
namespace Observer
{
	class GoalObserver;
	class ResultObserver;
}

class SceneMain : public SceneBase
{
public:

	SceneMain();
	~SceneMain() = default;

	void OnInit();

	std::unique_ptr<SceneBase> OnUpdate() override;

private:

	Player* mPlayer;

	Skybox* mSkybox;

	UI::UIManager* mUIManager;

	std::unique_ptr<Observer::GoalObserver> mGoalObserver;

	std::unique_ptr<Observer::ResultObserver> mResultObserver;
};
