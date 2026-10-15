#include "ResultScreen.h"
#include "../Core/UIRoot.h"
#include "../Widget/BoxObject.h"
#include "../Widget/MenuItem.h"
#include "../Widget/TextObject.h"
#include "System/ResourceManager.h"
#include "System/Resource/Font.h"
#include "System/Input/Literal/InputState.h"
#include "Utility/Color.h"
#include "World/Other/ResultRecorder.h"

namespace
{
	const char* const kSuccessText = "CLEAR!";
	const char* const kFailText = "FAILED...";
	const char* const kExitText = "Press Z to back to title";
	const char* const kScorePostfixText = " pt";

	constexpr Vector3 kResultPos{ 0.0f, 50.0f, 0.0f };
	constexpr Vector3 kProgressPos{ 50.0f, 200.0f, 0.0f };
	constexpr Vector3 kItemUseCountPos{ 50.0f, 300.0f, 0.0f };
	constexpr Vector3 kPlayTimePos{ 50.0f, 400.0f, 0.0f };
	constexpr float kScorePosX = -250.0f;
	constexpr Vector3 kOverallScorePos{ 0.0f, -150.0f, 0.0f };
	constexpr Vector3 kExitPos{ 0.0f, -50.0f, 0.0f };

	constexpr Vector2 kTextRect{ 400.0f, 100.0f };

	constexpr Vector3 kBackgroundPos{ 0.0f, 0.0f, 0.0f };
	constexpr Vector2 kBackgroundRect{ 750.0f, 700.0f };

	const char* const kFontPath = "Resources\\Font\\ShowcardGothic.dft";
	const char* const kFontSmallPath = "Resources\\Font\\ShowcardGothicSmall.dft";
}

namespace UI
{
	ResultScreen::ResultScreen(ResultRecorder* resultRecorder) :
		mResultText(nullptr),
		mProgressText(nullptr),
		mItemUseCountText(nullptr),
		mPlayTimeText(nullptr),
		mScoreDistanceText(nullptr),
		mScoreItemText(nullptr),
		mScoreTimeText(nullptr),
		mOverallScoreText(nullptr),
		mExitText(nullptr),
		mResultRecorder(resultRecorder)
	{
	}

	void ResultScreen::Init()
	{
		std::shared_ptr<Resource::ResourceBase> font = ResourceManager::GetInstance().GetResource<Resource::Font>(kFontPath);
		std::shared_ptr<Resource::ResourceBase> fontSmall = ResourceManager::GetInstance().GetResource<Resource::Font>(kFontSmallPath);

		BoxObject* bg = CreateToChild<UI::BoxObject>(Color::black);
		bg->GetRectTransform()->localPosition = kBackgroundPos;
		bg->GetRectTransform()->SetFullRectAsFixed(kBackgroundRect);

		// リザルト内容を表示するテキストオブジェクトを生成
		mResultText = bg->CreateToChild<UI::TextObject>(font, "", Color::white, HolizontalAlignment::Center, VerticalAlignment::Middle);
		mResultText->GetRectTransform()->localPosition = kResultPos;
		mResultText->GetRectTransform()->SetAnchor(RectTransform::Anchor::CenterTop);

		mProgressText = bg->CreateToChild<UI::TextObject>(fontSmall, "", Color::white, HolizontalAlignment::Left, VerticalAlignment::Middle);
		mProgressText->GetRectTransform()->localPosition = kProgressPos;
		mProgressText->GetRectTransform()->SetAnchor(RectTransform::Anchor::LeftTop);

		mItemUseCountText = bg->CreateToChild<UI::TextObject>(fontSmall, "", Color::white, HolizontalAlignment::Left, VerticalAlignment::Middle);
		mItemUseCountText->GetRectTransform()->localPosition = kItemUseCountPos;
		mItemUseCountText->GetRectTransform()->SetAnchor(RectTransform::Anchor::LeftTop);

		mPlayTimeText = bg->CreateToChild<UI::TextObject>(fontSmall, "", Color::white, HolizontalAlignment::Left, VerticalAlignment::Middle);
		mPlayTimeText->GetRectTransform()->localPosition = kPlayTimePos;
		mPlayTimeText->GetRectTransform()->SetAnchor(RectTransform::Anchor::LeftTop);

		// 各スコア
		mScoreDistanceText = bg->CreateToChild<UI::TextObject>(fontSmall, "", Color::white, HolizontalAlignment::Left, VerticalAlignment::Middle);
		mScoreDistanceText->GetRectTransform()->localPosition = Vector3(kScorePosX, kProgressPos.y, 0.0f);
		mScoreDistanceText->GetRectTransform()->SetAnchor(RectTransform::Anchor::RightTop);

		mScoreItemText = bg->CreateToChild<UI::TextObject>(fontSmall, "", Color::white, HolizontalAlignment::Left, VerticalAlignment::Middle);
		mScoreItemText->GetRectTransform()->localPosition = Vector3(kScorePosX, kItemUseCountPos.y, 0.0f);
		mScoreItemText->GetRectTransform()->SetAnchor(RectTransform::Anchor::RightTop);

		mScoreTimeText = bg->CreateToChild<UI::TextObject>(fontSmall, "", Color::white, HolizontalAlignment::Left, VerticalAlignment::Middle);
		mScoreTimeText->GetRectTransform()->localPosition = Vector3(kScorePosX, kPlayTimePos.y, 0.0f);
		mScoreTimeText->GetRectTransform()->SetAnchor(RectTransform::Anchor::RightTop);

		mOverallScoreText = bg->CreateToChild<UI::TextObject>(font, "", Color::yellow, HolizontalAlignment::Center, VerticalAlignment::Middle);
		mOverallScoreText->GetRectTransform()->localPosition = kOverallScorePos;
		mOverallScoreText->GetRectTransform()->SetAnchor(RectTransform::Anchor::CenterBottom);

		// 終了案内
		mExitText = bg->CreateToChild<UI::TextObject>(fontSmall, kExitText, Color::white, HolizontalAlignment::Center, VerticalAlignment::Middle);
		mExitText->GetRectTransform()->localPosition = kExitPos;
		mExitText->GetRectTransform()->SetAnchor(RectTransform::Anchor::CenterBottom);

		// 選択はせずに決定ボタンを受け付けるだけのため、ボタン単体で生成
		auto exitButton = GetMenuItemRoot()->CreateToChild<UI::MenuItem>();
		exitButton->SetSubmitCallback([this]()
			{
				this->SetCommand(Command::ExitResult);
				return true;
			});
		AddMenuItem(exitButton);
	}

	void ResultScreen::Update()
	{
	}

	void ResultScreen::Setup()
	{
		MenuScreen::Setup();

		ResultData result = mResultRecorder->CreateResultData();

		// リザルト内容をテキストに反映
		mResultText->SetDisplayText(result.isSuccessed ? kSuccessText : kFailText);
		mResultText->SetColor(result.isSuccessed ? Color::yellow : Color::magenta);

		mProgressText->SetDisplayText("Progress " + std::to_string(result.progressDistance) + "m");
		mScoreDistanceText->SetDisplayText(std::to_string(result.distanceScore) + kScorePostfixText);

		mItemUseCountText->SetDisplayText("Item Used " + std::to_string(result.itemUseCount));
		mScoreItemText->SetDisplayText(std::to_string(result.itemScore) + kScorePostfixText);

		std::string minutes = std::to_string(result.playMinutes);
		std::string seconds = (result.playSeconds < 10 ? "0" : "") + std::to_string(result.playSeconds);
		mPlayTimeText->SetDisplayText("Play Time " + minutes + ": " + seconds);
		mScoreTimeText->SetDisplayText(std::to_string(result.timeScore) + kScorePostfixText);

		int overallScore = result.distanceScore + result.itemScore + result.timeScore;
		mOverallScoreText->SetDisplayText(std::to_string(overallScore) + kScorePostfixText);
	}

	bool ResultScreen::ProcessInput(const Input::UIInputState& input)
	{
		if (input.submit)
		{
			if (!InvokeSubmit()) return false;
		}

		return true;
	}
}
