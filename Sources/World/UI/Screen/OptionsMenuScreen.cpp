#include "OptionsMenuScreen.h"
#include "../Widget/BoxObject.h"
#include "System/Input/Literal/InputState.h"

namespace UI
{
	OptionsMenuScreen::OptionsMenuScreen()
	{
	}

	void OptionsMenuScreen::Init()
	{
		BoxObject* bg = CreateToChild<UI::BoxObject>(Color::black);
		bg->GetRectTransform()->SetAnchor(RectTransform::Anchor::FullStretch);
	}

	void OptionsMenuScreen::Update()
	{
	}

	void OptionsMenuScreen::Draw()
	{
	}

	void OptionsMenuScreen::Setup()
	{
		MenuScreen::Setup();
	}

	bool OptionsMenuScreen::ProcessInput(const Input::UIInputState& input)
	{
		if (input.up)
		{
			MoveCursorPrev();
		}
		if (input.down)
		{
			MoveCursorNext();
		}
		if (input.submit)
		{
			if (!InvokeSubmit()) return false;
		}
		if (input.cancel)
		{
			if (!InvokeCancel()) return false;
		}

		return true;
	}
}
