#include "SceneMain.h"
#include "SceneTitle.h"
#include "Camera/CameraFollow.h"
#include "Camera/CameraManager.h"
#include "Factory/PlayerCreator.h"
#include "Observer/GoalObserver.h"
#include "Observer/ResultObserver.h"
#include "Observer/Subject.h"
#include "System/InputManager.h"
#include "System/ResourceManager.h"
#include "System/Input/Mouse.h"
#include "System/Resource/Model.h"
#include "World/Character/Player.h"
#include "World/Object/DeathCloud.h"
#include "World/Object/GoalObject.h"
#include "World/Object/GoalTrigger.h"
#include "World/Object/Skybox.h"
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

	const char* const kHelicopterModelPath = "Resources\\Model\\Helicopter\\helicopter.mv1";

	constexpr float kGoalY = 5000.0f;

	constexpr Vector3 kDeathCloudOffsetPlayer{ 0.0f, -500.0f, 0.0f };
}

SceneMain::SceneMain() :
	mPlayer(nullptr),
	mSkybox(nullptr),
	mDeathCloud(nullptr),
	mUIManager(nullptr),
	mDifficultyData{}
{
}

SceneMain::SceneMain(const StageDifficultyData& difficultyData) :
	mPlayer(nullptr),
	mSkybox(nullptr),
	mDeathCloud(nullptr),
	mUIManager(nullptr),
	mDifficultyData(difficultyData)
{
}

void SceneMain::OnInit()
{
	std::shared_ptr<Resource::ResourceBase> skyboxModel = ResourceManager::GetInstance().GetResource<Resource::Model>(kSkyboxModelPath);
	mSkybox = CreateToRoot<Skybox>(skyboxModel);

	std::shared_ptr<Resource::ResourceBase> goalModel = ResourceManager::GetInstance().GetResource<Resource::Model>(kHelicopterModelPath);
	StageManager* stageManager = CreateToRoot<StageManager>(goalModel, kGoalY);

	ResultRecorder* resultRecorder = CreateToRoot<ResultRecorder>();

	ItemObjectManager* itemObjectManager = CreateToRoot<ItemObjectManager>(mDifficultyData.itemNum, resultRecorder);

	std::unique_ptr<PlayerCreator> playerCreator = std::make_unique<PlayerCreator>(itemObjectManager);
	mPlayer = AddToRoot<Player>(std::move(playerCreator->CreateInstance()));

	mUIManager = CreateToRoot<UI::UIManager>();
	mUIManager->AddScreenToPool(std::make_unique<UI::InGameScreen>(kGoalY, mPlayer->GetTransform(), itemObjectManager));
	mUIManager->AddScreenToPool(std::make_unique<UI::GoalEventScreen>());
	mUIManager->AddScreenToPool(std::make_unique<UI::ResultScreen>(resultRecorder));
	mUIManager->PushScreen<UI::InGameScreen>();

	mGoalObserver = std::make_unique<Observer::GoalObserver>(mUIManager);
	mResultObserver = std::make_unique<Observer::ResultObserver>(resultRecorder, mUIManager, mPlayer->GetTransform());

	GoalTrigger* goalTrigger = stageManager->GetGoalObject()->GetTrigger();
	goalTrigger->GetEventSubject()->RegisterObserver(mPlayer->GetObserver());
	goalTrigger->GetEventSubject()->RegisterObserver(mGoalObserver.get());
	goalTrigger->GetEventSubject()->RegisterObserver(mResultObserver.get());

	Vector3 cloudInitPos = mPlayer->GetTransform()->localPosition + kDeathCloudOffsetPlayer;
	Vector3 goalPos = stageManager->GetGoalObject()->GetTransform()->CalculateWorldPosition();
	mDeathCloud = CreateToRoot<DeathCloud>(cloudInitPos, goalPos, mDifficultyData.cloudSpeed);
	mDeathCloud->GetEventSubject()->RegisterObserver(mPlayer->GetObserver());
	mDeathCloud->GetEventSubject()->RegisterObserver(mResultObserver.get());

	CreateToRoot<ItemSpawnerManager>(stageManager, mPlayer->GetLandTerrainRecorder(), itemObjectManager, mDifficultyData.itemNum);

	GetCameraManager()->AddCamera(Camera::Type::Follow, std::make_unique<CameraFollow>(mPlayer->GetTransform()));
	GetCameraManager()->SetCurrentCameraType(Camera::Type::Follow);

	Mouse::GetInstance().SetMode(Mouse::Mode::Relative);
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
		return std::make_unique<SceneTitle>();
	}

	return nullptr;
}
