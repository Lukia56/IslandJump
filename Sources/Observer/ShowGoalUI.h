#pragma once

#include "IObserver.h"

namespace UI
{
	class UIManager;
}

namespace Observer
{
	class ShowGoalUI : public IObserver
	{
	public:

		ShowGoalUI(UI::UIManager* uiManager);
		~ShowGoalUI() = default;

		void OnNotify(Event event) override;

	private:

		UI::UIManager* mUIManager;
	};
}

