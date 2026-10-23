#pragma once
#include "MenuScreen.h"

namespace UI
{
	class TextObject;

	class OptionsMenuScreen : public MenuScreen
	{
	public:

		OptionsMenuScreen();
		~OptionsMenuScreen() = default;

		void Init() override;
		void Update() override;
		void Draw() override;

		void Setup() override;

		bool ProcessInput(const Input::UIInputState& input);

	private:

		TextObject* mMouseSensitivityXValueText;
		TextObject* mMouseSensitivityYValueText;
	};
}
