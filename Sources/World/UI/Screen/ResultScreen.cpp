#include "ResultScreen.h"
#include "../Widget/TextObject.h"
#include "../Widget/BoxObject.h"
#include "System/ResourceManager.h"
#include "System/Resource/Font.h"
#include "Utility/Color.h"
#include "World/Other/ResultRecorder.h"

namespace
{
	const char* const kSuccessText = "CLEAR!";
	const char* const kFailText = "FAILED...";

	constexpr Vector3 kResultPos{ 0.0f, -300.0f, 0.0f };
	constexpr Vector3 kProgressPos{ 0.0f, -100.0f, 0.0f };
	constexpr Vector3 kItemUseCountPos{ 0.0f, 0.0f, 0.0f };
	constexpr Vector3 kPlayTimePos{ 0.0f, 100.0f, 0.0f };

	constexpr Vector2 kTextRect{ 500.0f, 100.0f };

	constexpr Vector3 kBackgroundPos{ 0.0f, 0.0f, 0.0f };
	constexpr Vector2 kBackgroundRect{ 700.0f, 700.0f };

	const char* const kFontPath = "Resources\\Font\\ShowcardGothic.dft";
}

namespace UI
{
	ResultScreen::ResultScreen(ResultRecorder* resultRecorder) :
		mResultText(nullptr),
		mProgressText(nullptr),
		mItemUseCountText(nullptr),
		mPlayTimeText(nullptr),
		mResultRecorder(resultRecorder)
	{
	}

	void ResultScreen::Init()
	{
		std::shared_ptr<Resource::ResourceBase> font = ResourceManager::GetInstance().GetResource<Resource::Font>(kFontPath);

		BoxObject* bg = CreateToChild<UI::BoxObject>(Color::black);
		bg->GetRectTransform()->localPosition = kBackgroundPos;
		bg->GetRectTransform()->SetFullRectAsFixed(kBackgroundRect);

		mResultText = CreateToChild<UI::TextObject>(font, "", Color::white, HolizontalAlignment::Center, VerticalAlignment::Middle);
		mResultText->GetRectTransform()->localPosition = kResultPos;
		mResultText->GetRectTransform()->SetFullRectAsFixed(kTextRect);

		mProgressText = CreateToChild<UI::TextObject>(font, "", Color::white, HolizontalAlignment::Left, VerticalAlignment::Middle);
		mProgressText->GetRectTransform()->localPosition = kProgressPos;
		mProgressText->GetRectTransform()->SetFullRectAsFixed(kTextRect);

		mItemUseCountText = CreateToChild<UI::TextObject>(font, "", Color::white, HolizontalAlignment::Left, VerticalAlignment::Middle);
		mItemUseCountText->GetRectTransform()->localPosition = kItemUseCountPos;
		mItemUseCountText->GetRectTransform()->SetFullRectAsFixed(kTextRect);

		mPlayTimeText = CreateToChild<UI::TextObject>(font, "", Color::white, HolizontalAlignment::Left, VerticalAlignment::Middle);
		mPlayTimeText->GetRectTransform()->localPosition = kPlayTimePos;
		mPlayTimeText->GetRectTransform()->SetFullRectAsFixed(kTextRect);
	}

	void ResultScreen::Update()
	{
	}

	void ResultScreen::Setup()
	{
		ResultData result = mResultRecorder->CreateResultData();

		mResultText->SetDisplayText(result.isSuccessed ? kSuccessText : kFailText);
		mResultText->SetColor(result.isSuccessed ? Color::yellow : Color::magenta);

		mProgressText->SetDisplayText("Progress " + std::to_string(result.progressDistance) + "m");

		mItemUseCountText->SetDisplayText("Item Used " + std::to_string(result.itemUseCount));

		std::string minutes = std::to_string(result.playMinutes);
		std::string seconds = (result.playSeconds < 10 ? "0" : "") + std::to_string(result.playSeconds);
		mPlayTimeText->SetDisplayText("Play Time " + minutes + ": " + seconds);
	}
}
