#include "ResultObserver.h"
#include "World/Other/ResultRecorder.h"
#include "World/UI/Core/UIManager.h"
#include "World/UI/Screen/ResultScreen.h"

namespace Observer
{
	ResultObserver::ResultObserver(ResultRecorder* resultRecorder, UI::UIManager* uiManager) :
		mResultRecorder(resultRecorder),
		mUIManager(uiManager)
	{
	}

	ResultObserver::ResultObserver(ResultRecorder* resultRecorder, UI::UIManager* uiManager, Transform* playerTransform) :
		mResultRecorder(resultRecorder),
		mUIManager(uiManager)
	{
	}

	void ResultObserver::OnNotify(Event event)
	{
		switch (event)
		{
		case Observer::Event::ReachGoal:
			mResultRecorder->SetSuccessed(true);
			mResultRecorder->SetCountPlayTimer(false);
			break;

		case Observer::Event::FallCloudPlayer:
			mResultRecorder->SetSuccessed(false);
			mResultRecorder->SetCountPlayTimer(false);
			break;

		case Observer::Event::TransitionResult:
			mUIManager->PushScreen<UI::ResultScreen>();
			break;
		}
	}
}
