#pragma once

#include "SceneBase.h"
#include "Param/Param.h"

class Player;
class Skybox;
class DeathCloud;
class ResultRecorder;
namespace UI
{
	class UIManager;
}
namespace Observer
{
	class IObserver;
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

	ResultRecorder* mResultRecorder;

	StageDifficultyData mDifficultyData;

	std::unique_ptr<Observer::IObserver> mGoalObserver;

	std::unique_ptr<Observer::IObserver> mResultObserver;

	std::unique_ptr<Observer::IObserver> mSoundObserver;

	std::unique_ptr<Observer::IObserver> mItemObserver;
};
