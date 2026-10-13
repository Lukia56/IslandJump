#include "SceneTitle.h"
#include "SceneMain.h"
#include "Application.h"
#include "Camera/CameraRotation.h"
#include "Camera/CameraManager.h"
#include "Observer/SoundObserver.h"
#include "Observer/Subject.h"
#include "System/InputManager.h"
#include "System/ResourceManager.h"
#include "System/SoundManager.h"
#include "System/Resource/Model.h"
#include "System/Resource/Sound.h"
#include "Utility/Data/CSV/CsvLoader.h"
#include "World/Object/Skybox.h"
#include "World/UI/Core/UIManager.h"
#include "World/UI/Screen/TitleMenuScreen.h"
#include "World/UI/Screen/DifficultyMenuScreen.h"

namespace
{
	constexpr Vector3 kCameraRotate{ 0.0f, 10.0f, 0.0f };

	const char* const kSkyboxModelPath = "Resources\\Model\\Skybox\\Skybox.mv1";

	const char* const kBGMPath = "Resources\\Sound\\BGM\\Title.ogg";

	const char* const kStageDifficultyDataPath = "Resources\\MasterData\\StageDifficultyData.csv";
}

SceneTitle::SceneTitle() :
	mUIManager(nullptr),
	mSoundObserver(nullptr)
{
}

void SceneTitle::OnInit()
{
	std::shared_ptr<Resource::ResourceBase> skyboxModel = ResourceManager::GetInstance().GetResource<Resource::Model>(kSkyboxModelPath);
	CreateToRoot<Skybox>(skyboxModel);

	mSoundObserver = std::make_unique<Observer::SoundObserver>();

	mUIManager = CreateToRoot<UI::UIManager>();

	std::unique_ptr<UI::TitleMenuScreen> titleMenuScreen = std::make_unique<UI::TitleMenuScreen>();
	titleMenuScreen->GetEventSubject()->RegisterObserver(mSoundObserver.get());
	mUIManager->AddScreenToPool(std::move(titleMenuScreen));

	std::unique_ptr<UI::DifficultyMenuScreen> difficultyMenuScreen = std::make_unique<UI::DifficultyMenuScreen>();
	difficultyMenuScreen->GetEventSubject()->RegisterObserver(mSoundObserver.get());
	mUIManager->AddScreenToPool(std::move(difficultyMenuScreen));

	mUIManager->PushScreen<UI::TitleMenuScreen>();

	GetCameraManager()->AddCamera(Camera::Type::Rotation, std::make_unique<CameraRotation>(Vector3::Zero, kCameraRotate));
	GetCameraManager()->SetCurrentCameraType(Camera::Type::Rotation);

	std::shared_ptr<Resource::ResourceBase> bgm = ResourceManager::GetInstance().GetResource<Resource::Sound>(kBGMPath);
	SoundManager::GetInstance().PlayBGM(bgm);
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
	case UI::Command::StartHardMode:
	{
		size_t index = static_cast<size_t>(command == UI::Command::StartEasyMode ? StageDifficultyData::Difficulty::Easy : StageDifficultyData::Difficulty::Hard);
		StageDifficultyData data = Data::Csv::LoadCsvAs<StageDifficultyData>(kStageDifficultyDataPath)[index];
		return std::make_unique<SceneMain>(data);
	}
	}

	return nullptr;
}
