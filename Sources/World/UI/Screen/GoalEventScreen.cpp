#include "GoalEventScreen.h"
#include "../Widget/TextObject.h"
#include "System/ResourceManager.h"
#include "System/Resource/Font.h"
#include "Utility/Color.h"

namespace
{
	const char* const kGoalText = "YOU ESCAPED!";

	const char* const kFontPath = "Resources\\Font\\ShowcardGothic.dft";
}

namespace UI
{
	GoalEventScreen::GoalEventScreen()
	{
	}

	void GoalEventScreen::Init()
	{
		std::shared_ptr<Resource::ResourceBase> font = ResourceManager::GetInstance().GetResource<Resource::Font>(kFontPath);

		UI::TextObject* text = CreateToChild<UI::TextObject>(font, kGoalText, Color::yellow, HolizontalAlignment::Center, VerticalAlignment::Middle);
		text->GetRectTransform()->SetFullRectAsFixed(Vector2(320, 100));
	}

	void GoalEventScreen::Update()
	{
	}

	void GoalEventScreen::Setup()
	{
	}
}
