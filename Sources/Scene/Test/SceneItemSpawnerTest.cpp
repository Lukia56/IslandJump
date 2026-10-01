#include "SceneItemSpawnerTest.h"
#include "SceneSelectDebug.h"
#include "World/Other/StageManager.h"
#include "Camera/CameraDebugFree.h"
#include "Camera/CameraManager.h"
#include "System/Input/Keyboard.h"
#include "World/Object/DebugGround.h"
#include "World/Other/ItemSpawnerManager.h"
#include "World/Character/Player.h"

namespace
{
	const char* const kStageDataPath = "Resources\\MasterData\\ItemSpawnerTest.json";
}

SceneItemSpawnerTest::SceneItemSpawnerTest()
{
}

void SceneItemSpawnerTest::OnInit()
{
	Player* player = CreateToRoot<Player>();
	player->GetTransform()->localPosition = Vector3(100.0f, 200.0f, 0.0f);

	CreateToRoot<DebugGround>();

	StageManager* stageManager = CreateToRoot<StageManager>(kStageDataPath);
	CreateToRoot<ItemSpawnerManager>(stageManager);

	GetCameraManager()->AddCamera(Camera::Type::Follow, std::make_unique<CameraDebugFree>());
	GetCameraManager()->SetCurrentCameraType(Camera::Type::Follow);
}

std::unique_ptr<SceneBase> SceneItemSpawnerTest::OnUpdate()
{
	if (Keyboard::GetInstance().IsDown(KEY_INPUT_Q))
	{
		return std::make_unique<SceneSelectDebug>();
	}

	return nullptr;
}
