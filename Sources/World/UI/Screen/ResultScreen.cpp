#include "ResultScreen.h"
#include "../Widget/TextObject.h"
#include "System/ResourceManager.h"
#include "System/Resource/Font.h"
#include "Utility/Color.h"

namespace
{
	const char* const kResultText = "RESULT";

	const char* const kFontPath = "Resources\\Font\\ShowcardGothic.dft";
}

namespace UI
{
	ResultScreen::ResultScreen()
	{
	}

	void ResultScreen::Init()
	{
		std::shared_ptr<Resource::ResourceBase> font = ResourceManager::GetInstance().GetResource<Resource::Font>(kFontPath);

		UI::TextObject* text = CreateToChild<UI::TextObject>(font, kResultText, Color::yellow, HolizontalAlignment::Center, VerticalAlignment::Middle);
		text->GetRectTransform()->localPosition = Vector3(0.0f, 300.0f, 0.0f);
		text->GetRectTransform()->SetFullRectAsFixed(Vector2(320, 100));
	}

	void ResultScreen::Update()
	{
	}
}
