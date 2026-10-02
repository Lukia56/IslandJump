#pragma once

#include "../Core/Screen.h"

namespace UI
{
	class GoalEventScreen : public Screen
	{
	public:

		GoalEventScreen();
		~GoalEventScreen() = default;

		void Init() override;
		void Update() override;

		void Setup() override;
	};
}

