#include "GoalObserver.h"
#include "World/UI/Core/UIManager.h"
#include "World/UI/Screen/GoalEventScreen.h"

namespace Observer
{
	GoalObserver::GoalObserver(UI::UIManager* uiManager) :
		mUIManager(uiManager)
	{
	}

	void GoalObserver::OnNotify(Event event)
	{
		if (event != Event::ReachGoal) return;
		
		mUIManager->PushScreen<UI::GoalEventScreen>();
	}
}
