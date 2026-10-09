#include "ResultObserver.h"
#include "World/Other/ResultRecorder.h"
#include "World/UI/Core/UIManager.h"
#include "World/UI/Screen/ResultScreen.h"

namespace Observer
{
	ResultObserver::ResultObserver(ResultRecorder* resultRecorder, UI::UIManager* uiManager) :
		mResultRecorder(resultRecorder),
		mUIManager(uiManager),
		mPlayerTransform(nullptr)
	{
	}

	ResultObserver::ResultObserver(ResultRecorder* resultRecorder, UI::UIManager* uiManager, Transform* playerTransform) :
		mResultRecorder(resultRecorder),
		mUIManager(uiManager),
		mPlayerTransform(playerTransform)
	{
	}

	void ResultObserver::OnNotify(Event event)
	{
		switch (event)
		{
		case Observer::Event::ReachGoal:
			mResultRecorder->SetProgressDistance(static_cast<int>(mPlayerTransform->CalculateWorldPosition().y));
			mResultRecorder->SetSuccessed(true);
			break;

		case Observer::Event::FallCloudPlayer:
			mResultRecorder->SetProgressDistance(static_cast<int>(mPlayerTransform->CalculateWorldPosition().y));
			mResultRecorder->SetSuccessed(false);
			break;

		case Observer::Event::TransitionResult:
			mUIManager->PushScreen<UI::ResultScreen>();
			break;
		}
	}
}
