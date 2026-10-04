#include "SceneLoadStageTest.h"
#include "Camera/CameraDebugFree.h"
#include "Camera/CameraManager.h"
#include "World/Other/StageManager.h"

SceneLoadStageTest::SceneLoadStageTest()
{
}

void SceneLoadStageTest::OnInit()
{
	CreateToRoot<StageManager>();

	GetCameraManager()->AddCamera(Camera::Type::DebugFree, std::make_unique<CameraDebugFree>());
	GetCameraManager()->SetCurrentCameraType(Camera::Type::DebugFree);
}

std::unique_ptr<SceneBase> SceneLoadStageTest::OnUpdate()
{
	return nullptr;
}
