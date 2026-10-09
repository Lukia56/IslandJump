#pragma once

#include "MenuScreen.h"

namespace UI
{
	class DifficultyMenuScreen : public MenuScreen
	{
    public:

        DifficultyMenuScreen();
        ~DifficultyMenuScreen() = default;

        void Init() override;

        void Update() override;

        void Setup() override;

        bool ProcessInput(const Input::UIInputState& input);
	};
}
