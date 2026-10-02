#include "SceneGoalTest.h"
#include "SceneSelectDebug.h"
#include "Camera/CameraFollow.h"
#include "Camera/CameraManager.h"
#include "Observer/ShowGoalUI.h"
#include "Observer/Subject.h"
#include "System/Input/Keyboard.h"
#include "System/Input/Mouse.h"
#include "World/Character/Player.h"
#include "World/Object/DebugGround.h"
#include "World/Object/GoalTrigger.h"
#include "World/Test/TestTerrain.h"
#include "World/UI/Core/UIManager.h"
#include "World/UI/Screen/GoalEventScreen.h"

SceneGoalTest::SceneGoalTest() :
	mPlayer(nullptr),
	mUIManager(nullptr)
{
}

void SceneGoalTest::OnInit()
{
	CreateToRoot<DebugGround>();

	mPlayer = CreateToRoot<Player>();
	mPlayer->GetTransform()->localPosition = Vector3(100.0f, 200.0f, 0.0f);

	GoalTrigger* goal = CreateToRoot<GoalTrigger>();
	goal->GetTransform()->localPosition = Vector3(0.0f, 200.0f, -300.0f);

	CreateToRoot<TestTerrain>(Vector3(1000.0f, 100.0f, 1000.0f));

	mUIManager = CreateToRoot<UI::UIManager>();
	mUIManager->AddScreenToPool(std::make_unique<UI::GoalEventScreen>());

	mShowGoalUI = std::make_unique<Observer::ShowGoalUI>(mUIManager);

	goal->GetEventSubject()->RegisterObserver(mShowGoalUI.get());

	GetCameraManager()->AddCamera(Camera::Type::Follow, std::make_unique<CameraFollow>(mPlayer->GetTransform()));
	GetCameraManager()->SetCurrentCameraType(Camera::Type::Follow);

	Mouse::GetInstance().SetMode(Mouse::Mode::Relative);
}

std::unique_ptr<SceneBase> SceneGoalTest::OnUpdate()
{
	mPlayer->SetCameraView(GetCameraManager()->GetCameraView());

	if (Keyboard::GetInstance().IsDown(KEY_INPUT_Q))
	{
		return std::make_unique<SceneSelectDebug>();
	}

	return nullptr;
}
