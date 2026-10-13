#pragma once

#include "SceneBase.h"
#include "Param/Param.h"

class Player;
class Skybox;
class DeathCloud;
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
	SceneMain(const StageDifficultyData& difficultyData);
	~SceneMain() = default;

	void OnInit();

	std::unique_ptr<SceneBase> OnUpdate() override;

private:

	Player* mPlayer;

	Skybox* mSkybox;

	DeathCloud* mDeathCloud;

	UI::UIManager* mUIManager;

	StageDifficultyData mDifficultyData;

	std::unique_ptr<Observer::GoalObserver> mGoalObserver;

	std::unique_ptr<Observer::ResultObserver> mResultObserver;
};
