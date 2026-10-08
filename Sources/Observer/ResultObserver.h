#pragma once

#include "IObserver.h"

namespace UI
{
	class UIManager;
}

namespace Observer
{
	class ResultObserver : public IObserver
	{
	public:

		ResultObserver(UI::UIManager* uiManager);
		~ResultObserver() = default;

		void OnNotify(Event event) override;

	private:

		UI::UIManager* mUIManager;
	};
}
