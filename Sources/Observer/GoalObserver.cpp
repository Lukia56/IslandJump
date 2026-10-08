#include "GoalObserver.h"
#include "World/UI/Core/UIManager.h"
#include "World/UI/Screen/GoalEventScreen.h"
#include "World/UI/Screen/ResultScreen.h"

namespace Observer
{
	GoalObserver::GoalObserver(UI::UIManager* uiManager) :
		mUIManager(uiManager)
	{
	}

	void GoalObserver::OnNotify(Event event)
	{
		if (event == Event::ReachGoal)
		{
			mUIManager->PushScreen<UI::GoalEventScreen>();
		}
		else
		if (event == Event::TransitionResult)
		{
			mUIManager->PopScreen();
			mUIManager->PushScreen<UI::ResultScreen>();
		}
	}
}
