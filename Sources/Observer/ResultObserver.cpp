#include "ResultObserver.h"
#include "World/UI/Core/UIManager.h"
#include "World/UI/Screen/ResultScreen.h"

namespace Observer
{
	ResultObserver::ResultObserver(UI::UIManager* uiManager) :
		mUIManager(uiManager)
	{
	}

	void ResultObserver::OnNotify(Event event)
	{
		// TODO: ‚±‚±‚ÅƒNƒŠƒA‚©Ž¸”s‚©Ý’è‚·‚é
		switch (event)
		{
		case Observer::Event::ReachGoal:
			break;

		case Observer::Event::FallCloudPlayer:

			break;

		case Observer::Event::TransitionResult:
			mUIManager->PushScreen<UI::ResultScreen>();
			break;
		}
	}
}
