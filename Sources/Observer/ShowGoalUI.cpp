#include "ShowGoalUI.h"
#include "World/UI/Core/UIManager.h"
#include "World/UI/Screen/GoalEventScreen.h"

namespace Observer
{
	ShowGoalUI::ShowGoalUI(UI::UIManager* uiManager) :
		mUIManager(uiManager)
	{
	}

	void ShowGoalUI::OnNotify(Event event)
	{
		if (event != Event::ReachGoal) return;

		mUIManager->PushScreen<UI::GoalEventScreen>();
	}
}
