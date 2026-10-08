#include "SceneResultTest.h"
#include "SceneSelectDebug.h"
#include "Camera/CameraFollow.h"
#include "Camera/CameraManager.h"
#include "Observer/GoalObserver.h"
#include "Observer/Subject.h"
#include "System/ResourceManager.h"
#include "System/Resource/Model.h"
#include "System/Input/Keyboard.h"
#include "System/Input/Mouse.h"
#include "Utility/Data/CSV/CsvLoader.h"
#include "World/Character/Player.h"
#include "World/Object/DebugGround.h"
#include "World/Object/GoalTrigger.h"
#include "World/Test/TestTerrain.h"
#include "World/UI/Core/UIManager.h"
#include "World/UI/Screen/GoalEventScreen.h"
#include "World/UI/Screen/ResultScreen.h"

namespace
{
	const char* const kPlayerModelPath = "Resources\\Model\\Player.mv1";
	const char* const kPlayerAnimationParamPath = "Resources\\MasterData\\PlayerAnimationParam.csv";
}

SceneResultTest::SceneResultTest() :
	mPlayer(nullptr),
	mUIManager(nullptr),
	mGoalObserver(nullptr)
{
}

void SceneResultTest::OnInit()
{
	CreateToRoot<DebugGround>();

	std::shared_ptr<Resource::ResourceBase> playerModel = ResourceManager::GetInstance().GetResource<Resource::Model>(kPlayerModelPath);
	std::vector<AnimationParam> playerAnimParams = Data::Csv::LoadCsvAs<AnimationParam>(kPlayerAnimationParamPath);
	mPlayer = CreateToRoot<Player>(playerModel, playerAnimParams, nullptr);
	mPlayer->GetTransform()->localPosition = Vector3(100.0f, 200.0f, 0.0f);

	GoalTrigger* goal = CreateToRoot<GoalTrigger>();
	goal->GetTransform()->localPosition = Vector3(0.0f, 200.0f, -300.0f);

	CreateToRoot<TestTerrain>(Vector3(1000.0f, 100.0f, 1000.0f));

	mUIManager = CreateToRoot<UI::UIManager>();
	mUIManager->AddScreenToPool(std::make_unique<UI::GoalEventScreen>());
	mUIManager->AddScreenToPool(std::make_unique<UI::ResultScreen>());

	mGoalObserver = std::make_unique<Observer::GoalObserver>(mUIManager);

	goal->GetEventSubject()->RegisterObserver(mPlayer->GetObserver());
	goal->GetEventSubject()->RegisterObserver(mGoalObserver.get());

	GetCameraManager()->AddCamera(Camera::Type::Follow, std::make_unique<CameraFollow>(mPlayer->GetTransform()));
	GetCameraManager()->SetCurrentCameraType(Camera::Type::Follow);

	Mouse::GetInstance().SetMode(Mouse::Mode::Relative);
}

std::unique_ptr<SceneBase> SceneResultTest::OnUpdate()
{
	mPlayer->SetCameraView(GetCameraManager()->GetCameraView());

	if (Keyboard::GetInstance().IsDown(KEY_INPUT_Q))
	{
		return std::make_unique<SceneSelectDebug>();
	}

	return nullptr;
}
