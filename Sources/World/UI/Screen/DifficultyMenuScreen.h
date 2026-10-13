#pragma once

#include "MenuScreen.h"

namespace Observer
{
	class Subject;
}

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

	public:

		Observer::Subject* GetEventSubject() const { return mEventSubject.get(); }

	private:

		std::unique_ptr<Observer::Subject> mEventSubject;
	};
}
