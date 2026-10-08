#include "SceneItemSpawnerTest.h"
#include "SceneSelectDebug.h"
#include "Camera/CameraDebugFree.h"
#include "Camera/CameraFollow.h"
#include "Camera/CameraManager.h"
#include "Factory/PlayerCreator.h"
#include "System/Input/Keyboard.h"
#include "World/Character/Player.h"
#include "World/Object/DebugGround.h"
#include "World/Other/ItemObjectManager.h"
#include "World/Other/ItemSpawnerManager.h"
#include "World/Other/StageManager.h"

namespace
{
	const char* const kStageDataPath = "Resources\\MasterData\\ItemSpawnerTest.json";

	constexpr int kItemNum = 10;
}

SceneItemSpawnerTest::SceneItemSpawnerTest() :
	mPlayer(nullptr)
{
}

void SceneItemSpawnerTest::OnInit()
{
	CreateToRoot<DebugGround>();

	StageManager* stageManager = CreateToRoot<StageManager>(kStageDataPath);

	ItemObjectManager* itemObjectManager = CreateToRoot<ItemObjectManager>(kItemNum);

	std::unique_ptr<PlayerCreator> playerCreator = std::make_unique<PlayerCreator>(itemObjectManager);
	mPlayer = AddToRoot<Player>(std::move(playerCreator->CreateInstance()));
	mPlayer->GetTransform()->localPosition = Vector3(100.0f, 200.0f, 0.0f);

	CreateToRoot<ItemSpawnerManager>(stageManager, mPlayer->GetLandTerrainRecorder(), itemObjectManager, kItemNum);

	GetCameraManager()->AddCamera(Camera::Type::DebugFree, std::make_unique<CameraDebugFree>());
	GetCameraManager()->AddCamera(Camera::Type::Follow, std::make_unique<CameraFollow>(mPlayer->GetTransform()));
	GetCameraManager()->SetCurrentCameraType(Camera::Type::Follow);
}

std::unique_ptr<SceneBase> SceneItemSpawnerTest::OnUpdate()
{
	mPlayer->SetCameraView(GetCameraManager()->GetCameraView());

	if (Keyboard::GetInstance().IsDown(KEY_INPUT_Q))
	{
		return std::make_unique<SceneSelectDebug>();
	}

	return nullptr;
}
