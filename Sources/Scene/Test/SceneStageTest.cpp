#include "SceneStageTest.h"
#include "SceneSelectDebug.h"
#include "World/Character/Player.h"
#include "World/Test/TestTerrain.h"
#include "Camera/CameraFollow.h"
#include "Camera/CameraManager.h"
#include "System/Input/Keyboard.h"
#include "System/Input/Mouse.h"

SceneStageTest::SceneStageTest() :
	mPlayer(nullptr)
{
}

void SceneStageTest::OnInit()
{
	mPlayer = CreateToRoot<Player>();
	mPlayer->GetTransform()->Translate(0.0f, 100.0f, 0.0f);

	CreateToRoot<TestTerrain>(Vector3(1000.0f, 100.0f, 1000.0f));

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
