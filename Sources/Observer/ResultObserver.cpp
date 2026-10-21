#include "ResultObserver.h"
#include "Camera/CameraManager.h"
#include "World/Other/ResultRecorder.h"
#include "World/UI/Core/UIManager.h"
#include "World/UI/Screen/ResultScreen.h"

namespace Observer
{
	ResultObserver::ResultObserver(ResultRecorder* resultRecorder, UI::UIManager* uiManager, CameraManager* cameraManager) :
		mResultRecorder(resultRecorder),
		mUIManager(uiManager),
		mCameraManager(cameraManager)
	{
	}

	ResultObserver::ResultObserver(ResultRecorder* resultRecorder, UI::UIManager* uiManager, Transform* playerTransform) :
		mResultRecorder(resultRecorder),
		mUIManager(uiManager),
		mCameraManager(nullptr)
	{
	}

	void ResultObserver::OnNotify(Event event)
	{
		switch (event)
		{
		case Observer::Event::ReachGoal:
			mResultRecorder->SetSuccessed(true);
			mCameraManager->SetCurrentCameraType(Camera::Type::RotationGoal);
			break;

		case Observer::Event::FallCloudPlayer:
			mResultRecorder->SetSuccessed(false);
			mCameraManager->SetCurrentCameraType(Camera::Type::RotationPlayer);
			break;

		case Observer::Event::TransitionResult:
			mUIManager->PushScreen<UI::ResultScreen>();
			break;
		}
	}
}
