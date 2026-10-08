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
		if (event != Event::TransitionResult) return;

		mUIManager->PushScreen<UI::ResultScreen>();
	}
}
