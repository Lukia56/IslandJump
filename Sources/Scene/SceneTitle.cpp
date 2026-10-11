#include "SceneTitle.h"
#include "SceneMain.h"
#include "Application.h"
#include "Camera/CameraRotation.h"
#include "Camera/CameraManager.h"
#include "System/InputManager.h"
#include "System/ResourceManager.h"
#include "System/Resource/Model.h"
#include "World/Object/Skybox.h"
#include "World/UI/Core/UIManager.h"
#include "World/UI/Screen/TitleMenuScreen.h"
#include "World/UI/Screen/DifficultyMenuScreen.h"

namespace
{
	constexpr Vector3 kCameraRotate{ 0.0f, 10.0f, 0.0f };

	const char* const kSkyboxModelPath = "Resources\\Model\\Skybox\\Skybox.mv1";
}

SceneTitle::SceneTitle() :
	mUIManager(nullptr)
{
}

void SceneTitle::OnInit()
{
	std::shared_ptr<Resource::ResourceBase> skyboxModel = ResourceManager::GetInstance().GetResource<Resource::Model>(kSkyboxModelPath);
	CreateToRoot<Skybox>(skyboxModel);

	mUIManager = CreateToRoot<UI::UIManager>();
	mUIManager->AddScreenToPool(std::make_unique<UI::TitleMenuScreen>());
	mUIManager->AddScreenToPool(std::make_unique<UI::DifficultyMenuScreen>());
	mUIManager->PushScreen<UI::TitleMenuScreen>();

	GetCameraManager()->AddCamera(Camera::Type::Rotation, std::make_unique<CameraRotation>(Vector3::Zero, kCameraRotate));
	GetCameraManager()->SetCurrentCameraType(Camera::Type::Rotation);
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
		Application::isRunning = false;
		break;

	case UI::Command::StartEasyMode:
		return std::make_unique<SceneMain>();

	case UI::Command::StartHardMode:
		return std::make_unique<SceneMain>();
	}

	return nullptr;
}
