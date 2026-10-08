#include "ResultScreen.h"
#include "../Widget/TextObject.h"
#include "System/ResourceManager.h"
#include "System/Resource/Font.h"
#include "Utility/Color.h"
#include "World/Other/ResultRecorder.h"

namespace
{
	const char* const kTitleText = "RESULT";

	const char* const kSuccessText = "CLEAR";
	const char* const kFailText = "FAILED...";

	const char* const kFontPath = "Resources\\Font\\ShowcardGothic.dft";
}

namespace UI
{
	ResultScreen::ResultScreen(ResultRecorder* resultRecorder) :
		mResultText(nullptr),
		mResultRecorder(resultRecorder)
	{
	}

	void ResultScreen::Init()
	{
		std::shared_ptr<Resource::ResourceBase> font = ResourceManager::GetInstance().GetResource<Resource::Font>(kFontPath);

		UI::TextObject* title = CreateToChild<UI::TextObject>(font, kTitleText, Color::yellow, HolizontalAlignment::Center, VerticalAlignment::Middle);
		title->GetRectTransform()->localPosition = Vector3(0.0f, 300.0f, 0.0f);
		title->GetRectTransform()->SetFullRectAsFixed(Vector2(320, 100));

		mResultText = CreateToChild<UI::TextObject>(font, "", Color::white, HolizontalAlignment::Center, VerticalAlignment::Middle);
		mResultText->GetRectTransform()->localPosition = Vector3(0.0f, 100.0f, 0.0f);
		mResultText->GetRectTransform()->SetFullRectAsFixed(Vector2(320, 100));
	}

	void ResultScreen::Update()
	{
	}

	void ResultScreen::Setup()
	{
	}
}
