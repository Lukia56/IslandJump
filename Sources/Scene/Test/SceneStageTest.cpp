#include "SceneStageTest.h"
#include "SceneSelectDebug.h"
#include "Camera/CameraFollow.h"
#include "Camera/CameraManager.h"
#include "Observer/Subject.h"
#include "System/Input/Keyboard.h"
#include "System/Input/Mouse.h"
#include "World/Character/Player.h"
#include "World/Object/GoalObject.h"
#include "World/Object/GoalTrigger.h"
#include "World/Other/StageManager.h"

namespace
{
	const char* const kStageDataPath = "Resources\\MasterData\\MainStage.json";
}

SceneStageTest::SceneStageTest() :
	mPlayer(nullptr)
{
}

void SceneStageTest::OnInit()
{
	StageManager* stageManager = CreateToRoot<StageManager>();

	mPlayer = CreateToRoot<Player>();
	mPlayer->GetTransform()->Translate(0.0f, 100.0f, 0.0f);

	GoalTrigger* goalTrigger = stageManager->GetGoalObject()->GetTrigger();
	goalTrigger->GetEventSubject()->RegisterObserver(mPlayer->GetObserver());

	GetCameraManager()->AddCamera(Camera::Type::Follow, std::make_unique<CameraFollow>(mPlayer->GetTransform()));
	GetCameraManager()->SetCurrentCameraType(Camera::Type::Follow);

	Mouse::GetInstance().SetMode(Mouse::Mode::Relative);
}

std::unique_ptr<SceneBase> SceneStageTest::OnUpdate()
{
	mPlayer->SetCameraView(GetCameraManager()->GetCameraView());

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
