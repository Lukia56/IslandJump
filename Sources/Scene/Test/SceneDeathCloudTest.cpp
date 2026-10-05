#include "SceneDeathCloudTest.h"
#include "SceneSelectDebug.h"
#include "Camera/CameraFollow.h"
#include "Camera/CameraManager.h"
#include "Observer/Subject.h"
#include "System/Input/Keyboard.h"
#include "System/Input/Mouse.h"
#include "World/Character/Player.h"
#include "World/Object/DebugGround.h"
#include "World/Object/DeathCloud.h"
#include "World/Object/GoalObject.h"
#include "World/Test/TestTerrain.h"

namespace
{
	constexpr Vector3 kDeathCloudOffsetPlayer{ 0.0f, -800.0f, 0.0f };
}

SceneDeathCloudTest::SceneDeathCloudTest() :
	mPlayer(nullptr)
{
}

void SceneDeathCloudTest::OnInit()
{
	CreateToRoot<DebugGround>();

	mPlayer = CreateToRoot<Player>();
	mPlayer->GetTransform()->localPosition = Vector3(100.0f, 200.0f, 0.0f);

	GoalObject* goal = CreateToRoot<GoalObject>();
	goal->GetTransform()->localPosition = Vector3(0.0f, 600.0f, -300.0f);

	CreateToRoot<TestTerrain>(Vector3(1000.0f, 100.0f, 1000.0f));

	Vector3 cloudInitPos = mPlayer->GetTransform()->localPosition + kDeathCloudOffsetPlayer;
	Vector3 goalPos = goal->GetTransform()->CalculateWorldPosition();
	DeathCloud* cloud = CreateToRoot<DeathCloud>(cloudInitPos, goalPos);
	cloud->GetEventSubject()->RegisterObserver(mPlayer->GetObserver());

	GetCameraManager()->AddCamera(Camera::Type::Follow, std::make_unique<CameraFollow>(mPlayer->GetTransform()));
	GetCameraManager()->SetCurrentCameraType(Camera::Type::Follow);

	Mouse::GetInstance().SetMode(Mouse::Mode::Relative);
}

std::unique_ptr<SceneBase> SceneDeathCloudTest::OnUpdate()
{
	mPlayer->SetCameraView(GetCameraManager()->GetCameraView());

	if (Keyboard::GetInstance().IsDown(KEY_INPUT_Q))
	{
		return std::make_unique<SceneSelectDebug>();
	}

	return nullptr;
}
