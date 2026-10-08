#pragma once

#include "IObserver.h"

namespace UI
{
	class UIManager;
}

namespace Observer
{
	class GoalObserver : public IObserver
	{
	public:

		GoalObserver(UI::UIManager* uiManager);
		~GoalObserver() = default;

		void OnNotify(Event event) override;

	private:

		UI::UIManager* mUIManager;
	};
}

