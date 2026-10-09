#include "SceneTitle.h"
#include "System/InputManager.h"
#include "World/UI/Core/UIManager.h"
#include "World/UI/Screen/TitleMenuScreen.h"
#include "World/UI/Screen/DifficultyMenuScreen.h"

SceneTitle::SceneTitle() :
	mUIManager(nullptr)
{
}

void SceneTitle::OnInit()
{
	mUIManager = CreateToRoot<UI::UIManager>();
	mUIManager->AddScreenToPool(std::make_unique<UI::TitleMenuScreen>());
	mUIManager->AddScreenToPool(std::make_unique<UI::DifficultyMenuScreen>());
	mUIManager->PushScreen<UI::TitleMenuScreen>();
}

std::unique_ptr<SceneBase> SceneTitle::OnUpdate()
{
	mUIManager->ProcessInput(InputManager::GetInstance().GetUIInputState());

	UI::Command command = mUIManager->ConsumeCommand();
	switch (command)
	{
	case UI::Command::StartGame:
		mUIManager->PushScreen<UI::DifficultyMenuScreen>();
		break;

	case UI::Command::QuitGame:
		break;

	case UI::Command::StartEasyMode:
		break;

	case UI::Command::StartHardMode:
		break;
	}

	return nullptr;
}
