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
	const char* const kSuccessText = "クリア！";
	const char* const kFailText = "失敗…";
	const char* const kExitText = "スペースキーでタイトルへ戻る";
	const char* const kScorePostfixText = "pt";

	constexpr Vector3 kResultPos{ 0.0f, 50.0f, 0.0f };
	constexpr Vector3 kProgressPos{ 50.0f, 200.0f, 0.0f };
	constexpr Vector3 kItemUseCountPos{ 50.0f, 300.0f, 0.0f };
	constexpr float kScorePosX = -300.0f;
	constexpr Vector3 kOverallScorePos{ 0.0f, -150.0f, 0.0f };
	constexpr Vector3 kExitPos{ 0.0f, -50.0f, 0.0f };

	constexpr Vector2 kTextRect{ 400.0f, 100.0f };

	constexpr Vector3 kBackgroundPos{ 0.0f, 0.0f, 0.0f };
	constexpr Vector2 kBackgroundRect{ 900.0f, 550.0f };

	const char* const kFontPath = "Resources\\Font\\NicoKaku.dft";
	const char* const kFontSmallPath = "Resources\\Font\\NicoKakuSmall.dft";
}

namespace UI
{
	ResultScreen::ResultScreen(ResultRecorder* resultRecorder) :
		mResultText(nullptr),
		mProgressText(nullptr),
		mItemUseCountText(nullptr),
		mScoreDistanceText(nullptr),
		mScoreItemText(nullptr),
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

		// 各スコア
		mScoreDistanceText = bg->CreateToChild<UI::TextObject>(fontSmall, "", Color::white, HolizontalAlignment::Left, VerticalAlignment::Middle);
		mScoreDistanceText->GetRectTransform()->localPosition = Vector3(kScorePosX, kProgressPos.y, 0.0f);
		mScoreDistanceText->GetRectTransform()->SetAnchor(RectTransform::Anchor::RightTop);

		mScoreItemText = bg->CreateToChild<UI::TextObject>(fontSmall, "", Color::white, HolizontalAlignment::Left, VerticalAlignment::Middle);
		mScoreItemText->GetRectTransform()->localPosition = Vector3(kScorePosX, kItemUseCountPos.y, 0.0f);
		mScoreItemText->GetRectTransform()->SetAnchor(RectTransform::Anchor::RightTop);

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

		mProgressText->SetDisplayText("進んだ距離 " + std::to_string(result.progressDistance) + "m");
		mScoreDistanceText->SetDisplayText(std::to_string(result.distanceScore) + kScorePostfixText);

		mItemUseCountText->SetDisplayText("取得アイテム数 " + std::to_string(result.itemUseCount));
		mScoreItemText->SetDisplayText(std::to_string(result.itemScore) + kScorePostfixText);

		mOverallScoreText->SetDisplayText(std::to_string(result.overallScore) + kScorePostfixText);
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
