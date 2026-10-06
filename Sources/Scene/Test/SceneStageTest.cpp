#include "SceneStageTest.h"
#include "SceneSelectDebug.h"
#include "Camera/CameraFollow.h"
#include "Camera/CameraManager.h"
#include "Observer/Subject.h"
#include "System/ResourceManager.h"
#include "System/Resource/Model.h"
#include "System/Input/Keyboard.h"
#include "System/Input/Mouse.h"
#include "World/Character/Player.h"
#include "World/Object/GoalObject.h"
#include "World/Object/GoalTrigger.h"
#include "World/Object/Skybox.h"
#include "World/Other/ItemObjectManager.h"
#include "World/Other/ItemSpawnerManager.h"
#include "World/Other/StageManager.h"

namespace
{
	const char* const kSkyboxModelPath = "Resources\\Model\\Skybox\\Skybox.mv1";

	constexpr int kItemNum = 10;
}

SceneStageTest::SceneStageTest() :
	mPlayer(nullptr),
	mSkybox(nullptr)
{
}

void SceneStageTest::OnInit()
{
	std::shared_ptr<Resource::ResourceBase> skyboxModel = ResourceManager::GetInstance().GetResource<Resource::Model>(kSkyboxModelPath);
	mSkybox = CreateToRoot<Skybox>(skyboxModel);

	StageManager* stageManager = CreateToRoot<StageManager>();

	ItemObjectManager* itemObjectManager = CreateToRoot<ItemObjectManager>(kItemNum);

	mPlayer = CreateToRoot<Player>(itemObjectManager);
	mPlayer->GetTransform()->Translate(0.0f, 100.0f, 0.0f);

	GoalTrigger* goalTrigger = stageManager->GetGoalObject()->GetTrigger();
	goalTrigger->GetEventSubject()->RegisterObserver(mPlayer->GetObserver());

	CreateToRoot<ItemSpawnerManager>(stageManager, mPlayer->GetLandTerrainRecorder(), itemObjectManager, kItemNum);

	GetCameraManager()->AddCamera(Camera::Type::Follow, std::make_unique<CameraFollow>(mPlayer->GetTransform()));
	GetCameraManager()->SetCurrentCameraType(Camera::Type::Follow);

	Mouse::GetInstance().SetMode(Mouse::Mode::Relative);
}

std::unique_ptr<SceneBase> SceneStageTest::OnUpdate()
{
	mPlayer->SetCameraView(GetCameraManager()->GetCameraView());

	mSkybox->GetTransform()->localPosition = GetCameraManager()->GetCameraView().eyePosition;

	if (Keyboard::GetInstance().IsDown(KEY_INPUT_LALT))
	{
		Mouse::GetInstance().SetMode(Mouse::Mode::Absolute);
	}
	else
	{
		Mouse::GetInstance().SetMode(Mouse::Mode::Relative);
	}

	if (Keyboard::GetInstance().IsDown(KEY_INPUT_Q))
	{
		return std::make_unique<SceneSelectDebug>();
	}

	return nullptr;
}
