#include "SceneRayTest.h"
#include "Camera/CameraDebugFree.h"
#include "Camera/CameraManager.h"
#include "Collision/Collision3D.h"
#include "World/Test/TestCollider.h"
#include "World/Test/TestRay.h"

SceneRayTest::SceneRayTest()
{
}

void SceneRayTest::OnInit()
{
	CreateToRoot<TestRay>();
	CreateToRoot<TestCollider>(std::make_unique<Collision::AABB3D>(Vector3(100.0f, 100.0f, 100.0f)));

	GetCameraManager()->AddCamera(Camera::Type::DebugFree, std::make_unique<CameraDebugFree>());
	GetCameraManager()->SetCurrentCameraType(Camera::Type::DebugFree);
}

std::unique_ptr<SceneBase> SceneRayTest::OnUpdate()
{


	return nullptr;
}
