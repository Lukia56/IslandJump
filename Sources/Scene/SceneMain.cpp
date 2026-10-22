#include "SceneMain.h"
#include <filesystem>
#include "SceneTitle.h"
#include "Camera/CameraFollow.h"
#include "Camera/CameraRotation.h"
#include "Camera/CameraManager.h"
#include "Factory/PlayerCreator.h"
#include "Observer/ItemObserver.h"
#include "Observer/GoalObserver.h"
#include "Observer/ResultObserver.h"
#include "Observer/SoundObserver.h"
#include "Observer/Subject.h"
#include "System/InputManager.h"
#include "System/ResourceManager.h"
#include "System/SoundManager.h"
#include "System/UserDataManager.h"
#include "System/Input/Mouse.h"
#include "System/Resource/Effect.h"
#include "System/Resource/Model.h"
#include "System/Resource/Sound.h"
#include "World/Character/Player.h"
#include "World/Object/DeathCloud.h"
#include "World/Object/GoalObject.h"
#include "World/Object/GoalTrigger.h"
#include "World/Object/Skybox.h"
#include "World/Other/EffectManager.h"
#include "World/Other/ItemObjectManager.h"
#include "World/Other/ItemSpawnerManager.h"
#include "World/Other/ResultRecorder.h"
#include "World/Other/StageManager.h"
#include "World/UI/Core/UIManager.h"
#include "World/UI/Screen/GoalEventScreen.h"
#include "World/UI/Screen/InGameScreen.h"
#include "World/UI/Screen/ResultScreen.h"

namespace
{
	const char* const kPlayerModelPath = "Resources\\Model\\Player.mv1";
	const char* const kPlayerAnimationParamPath = "Resources\\MasterData\\PlayerAnimationParam.csv";

	const char* const kSkyboxModelPath = "Resources\\Model\\Skybox\\Skybox.mv1";
	const char* const kSkyboxHardModeModelPath = "Resources\\Model\\SkyboxHardMode\\Skybox.mv1";

	const char* const kCloudModelPath = "Resources\\Model\\Cloud.mv1";

	const char* const kHelicopterModelPath = "Resources\\Model\\Helicopter\\helicopter.mv1";

	const char* const kJumpBoostEffectPath = "Resources\\Effect\\ItemConsumeEffect_JumpBoost.efk";
	const char* const kSpeedBoostEffectPath = "Resources\\Effect\\ItemConsumeEffect_SpeedBoost.efk";
	const char* const kAerialControlEffectPath = "Resources\\Effect\\ItemConsumeEffect_AerialControl.efk";

	const char* const kBGMPath = "Resources\\Sound\\BGM\\InGame.ogg";

	constexpr Vector3 kDeathCloudOffsetPlayer{ 0.0f, -500.0f, 0.0f };

	constexpr Vector3 kCameraRotate{ 0.0f, 10.0f, 0.0f };
	constexpr Vector3 kRotationCameraEyeOffset{ 0.0f, 300.0f, 0.0f };
	constexpr float kCameraDistance = 1000.0f;

	constexpr int kMaxEffect = 100;
}

SceneMain::SceneMain() :
	mPlayer(nullptr),
	mSkybox(nullptr),
	mDeathCloud(nullptr),
	mUIManager(nullptr),
	mResultRecorder(nullptr),
	mDifficultyData{},
	mGoalObserver(nullptr),
	mResultObserver(nullptr),
	mSoundObserver(nullptr),
	mItemObserver(nullptr)
{
}

SceneMain::SceneMain(const StageDifficultyData& difficultyData) :
	mPlayer(nullptr),
	mSkybox(nullptr),
	mDeathCloud(nullptr),
	mUIManager(nullptr),
	mResultRecorder(nullptr),
	mDifficultyData(difficultyData),
	mGoalObserver(nullptr),
	mResultObserver(nullptr),
	mSoundObserver(nullptr),
	mItemObserver(nullptr)
{
}

void SceneMain::OnInit()
{
	std::string skyboxModelPath = mDifficultyData.difficulty == StageDifficultyData::Difficulty::Easy ? kSkyboxModelPath : kSkyboxHardModeModelPath;
	std::shared_ptr<Resource::ResourceBase> skyboxModel = ResourceManager::GetInstance().GetResource<Resource::Model>(skyboxModelPath);
	mSkybox = CreateToRoot<Skybox>(skyboxModel);

	std::shared_ptr<Resource::ResourceBase> goalModel = ResourceManager::GetInstance().GetResource<Resource::Model>(kHelicopterModelPath);
	StageManager* stageManager = CreateToRoot<StageManager>(goalModel, mDifficultyData.goalPosY);

	mResultRecorder = CreateToRoot<ResultRecorder>(&mDifficultyData);

	EffectManager* effectManager = CreateToRoot<EffectManager>(kMaxEffect);
	effectManager->RegisterEffect(ResourceManager::GetInstance().GetResource<Resource::Effect>(kJumpBoostEffectPath));
	effectManager->RegisterEffect(ResourceManager::GetInstance().GetResource<Resource::Effect>(kSpeedBoostEffectPath));
	effectManager->RegisterEffect(ResourceManager::GetInstance().GetResource<Resource::Effect>(kAerialControlEffectPath));

	ItemObjectManager* itemObjectManager = CreateToRoot<ItemObjectManager>(mDifficultyData.itemNum, mResultRecorder);

	std::unique_ptr<PlayerCreator> playerCreator = std::make_unique<PlayerCreator>(itemObjectManager);
	mPlayer = AddToRoot<Player>(std::move(playerCreator->CreateInstance()));

	mResultRecorder->SetPlayerTransform(mPlayer->GetTransform());

	Vector3 cloudInitPos = mPlayer->GetTransform()->localPosition + kDeathCloudOffsetPlayer;
	Vector3 goalPos = stageManager->GetGoalObject()->GetTransform()->CalculateWorldPosition();
	std::shared_ptr<Resource::ResourceBase> cloudModel = ResourceManager::GetInstance().GetResource<Resource::Model>(kCloudModelPath);
	mDeathCloud = CreateToRoot<DeathCloud>(cloudInitPos, goalPos, mDifficultyData.cloudSpeed, cloudModel);

	mUIManager = CreateToRoot<UI::UIManager>();
	mUIManager->AddScreenToPool(std::make_unique<UI::InGameScreen>(mDifficultyData.goalPosY, mPlayer->GetTransform(), mDeathCloud->GetTransform(), itemObjectManager, mResultRecorder));
	mUIManager->AddScreenToPool(std::make_unique<UI::GoalEventScreen>());
	mUIManager->AddScreenToPool(std::make_unique<UI::ResultScreen>(mResultRecorder));
	mUIManager->PushScreen<UI::InGameScreen>();

	mGoalObserver = std::make_unique<Observer::GoalObserver>(mUIManager);
	mResultObserver = std::make_unique<Observer::ResultObserver>(mResultRecorder, mUIManager, GetCameraManager(), mDeathCloud);
	mSoundObserver = std::make_unique<Observer::SoundObserver>();
	mItemObserver = std::make_unique<Observer::ItemObserver>(mPlayer->GetTransform(), effectManager);

	mPlayer->GetEventSubject()->RegisterObserver(mSoundObserver.get());
	mPlayer->GetEventSubject()->RegisterObserver(mItemObserver.get());

	GoalTrigger* goalTrigger = stageManager->GetGoalObject()->GetTrigger();
	goalTrigger->GetEventSubject()->RegisterObserver(mPlayer->GetObserver());
	goalTrigger->GetEventSubject()->RegisterObserver(mGoalObserver.get());
	goalTrigger->GetEventSubject()->RegisterObserver(mResultObserver.get());
	goalTrigger->GetEventSubject()->RegisterObserver(mSoundObserver.get());

	mDeathCloud->GetEventSubject()->RegisterObserver(mPlayer->GetObserver());
	mDeathCloud->GetEventSubject()->RegisterObserver(mResultObserver.get());
	mDeathCloud->GetEventSubject()->RegisterObserver(mSoundObserver.get());

	CreateToRoot<ItemSpawnerManager>(stageManager, mPlayer->GetLandTerrainRecorder(), itemObjectManager, mDifficultyData.itemNum);

	GetCameraManager()->AddCamera(Camera::Type::Follow, std::make_unique<CameraFollow>(mPlayer->GetTransform()));
	GetCameraManager()->AddCamera(Camera::Type::RotationPlayer, std::make_unique<CameraRotation>(mPlayer->GetTransform(), kCameraRotate, kCameraDistance, kRotationCameraEyeOffset));
	GetCameraManager()->AddCamera(Camera::Type::RotationGoal, std::make_unique<CameraRotation>(stageManager->GetGoalObject()->GetTransform(), kCameraRotate, kCameraDistance, kRotationCameraEyeOffset));
	GetCameraManager()->SetCurrentCameraType(Camera::Type::Follow);

	Mouse::GetInstance().SetMode(Mouse::Mode::Relative);

	std::shared_ptr<Resource::ResourceBase> bgm = ResourceManager::GetInstance().GetResource<Resource::Sound>(kBGMPath);
	SoundManager::GetInstance().PlayBGM(bgm);
}

std::unique_ptr<SceneBase> SceneMain::OnUpdate()
{
	mPlayer->SetCameraView(GetCameraManager()->GetCameraView());

	mSkybox->GetTransform()->localPosition = GetCameraManager()->GetCameraView().eyePosition;

	mDeathCloud->GetTransform()->localPosition.x = mPlayer->GetTransform()->localPosition.x;
	mDeathCloud->GetTransform()->localPosition.z = mPlayer->GetTransform()->localPosition.z;

	mUIManager->ProcessInput(InputManager::GetInstance().GetUIInputState());

	UI::Command command = mUIManager->ConsumeCommand();
	switch (command)
	{
	case UI::Command::ExitResult:
	{
		int score = mResultRecorder->CreateResultData().overallScore;

		SaveData& data = UserDataManager::GetInstance().GetTempSaveData();

		switch (mDifficultyData.difficulty)
		{
		case StageDifficultyData::Difficulty::Easy:
			if (data.easyHighscore < score) data.easyHighscore = score;
			break;

		case StageDifficultyData::Difficulty::Hard:
			if (data.hardHighscore < score) data.hardHighscore = score;
			break;
		}

		UserDataManager::GetInstance().ApplyTempSaveData();
		UserDataManager::GetInstance().ExportSaveData();

		return std::make_unique<SceneTitle>();
	}
	}

	return nullptr;
}
