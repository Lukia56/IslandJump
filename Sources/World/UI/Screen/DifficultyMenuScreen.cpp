#include "DifficultyMenuScreen.h"
#include <filesystem>
#include "../Widget/BoxObject.h"
#include "../Widget/MenuItem.h"
#include "../Widget/TextObject.h"
#include "Observer/Subject.h"
#include "System/ResourceManager.h"
#include "System/UserDataManager.h"
#include "System/Input/Literal/InputState.h"
#include "System/Resource/Font.h"

namespace
{
	const char* const kDescText = "Choose difficulty";
	const char* const kHighscoreDescText = "Highscore";

	constexpr Vector3 kDescPos{ 0.0f, 100.0f, 0.0f };
	constexpr Vector2 kDescRect{ 200.0f, 32.0f };

	const char* const kEasyModeText = "Easy";
	constexpr Vector3 kEasyModeTextPos{ 200.0f, -100.0f, 0.0f };

	const char* const kHardModeText = "Hard";
	constexpr Vector3 kHardModeTextPos{ -200.0f, -100.0f, 0.0f };

	constexpr Vector3 kHighscorePos{ 0.0f, -100.0f, 0.0f };
	constexpr Vector3 kHighscoreDescPos{ 0.0f, -25.0f, 0.0f };

	constexpr Vector2 kButtonRect{ 160.0f, 32.0f };

	constexpr Vector3 kBackgroundPos{ 0.0f, 0.0f, 0.0f };
	constexpr Vector2 kBackgroundRect{ 800.0f, 500.0f };

	const char* const kFontPath = "Resources\\Font\\ShowcardGothic.dft";
	const char* const kFontSmallPath = "Resources\\Font\\ShowcardGothicSmall.dft";
}

namespace UI
{
	DifficultyMenuScreen::DifficultyMenuScreen()
	{
		mEventSubject = std::make_unique<Observer::Subject>();

		// プッシュ時に項目オブジェクトが無いと初期選択がされないため、コンストラクタで生成

		BoxObject* bg = CreateToChild<UI::BoxObject>(Color::black);
		bg->GetRectTransform()->localPosition = kBackgroundPos;
		bg->GetRectTransform()->SetFullRectAsFixed(kBackgroundRect);

		std::shared_ptr<Resource::ResourceBase> font = ResourceManager::GetInstance().GetResource<Resource::Font>(kFontPath);
		std::shared_ptr<Resource::ResourceBase> fontSmall = ResourceManager::GetInstance().GetResource<Resource::Font>(kFontSmallPath);

		TextObject* descText = bg->CreateToChild<UI::TextObject>(font, kDescText, Color::white, HolizontalAlignment::Center, VerticalAlignment::Middle);
		descText->GetRectTransform()->localPosition = kDescPos;
		descText->GetRectTransform()->SetFullRectAsFixed(kDescRect);
		descText->GetRectTransform()->SetAnchor(RectTransform::Anchor::CenterTop);

		// イージーモード選択ボタン
		UI::MenuItem* easyModeButton = bg->CreateToChild<UI::MenuItem>();
		easyModeButton->GetRectTransform()->localPosition = kEasyModeTextPos;
		easyModeButton->GetRectTransform()->SetFullRectAsFixed(kButtonRect);
		easyModeButton->GetRectTransform()->SetAnchor(RectTransform::Anchor::LeftBottom);

		UI::TextObject* easyModeText = easyModeButton->CreateToChild<UI::TextObject>(font, kEasyModeText, Color::white, HolizontalAlignment::Center, VerticalAlignment::Middle);
		easyModeText->GetRectTransform()->SetAnchor(RectTransform::Anchor::FullStretch);

		easyModeButton->SetSelectCallback([easyModeText, this]()
			{
				easyModeText->SetColor(Color::green);
				mEventSubject->Notify(Observer::Event::UIMoveCursor);
			});
		easyModeButton->SetDeselectCallback([easyModeText]() { easyModeText->SetColor(Color::white); });
		easyModeButton->SetSubmitCallback([this]()
			{
				this->SetCommand(Command::StartEasyMode);
				mEventSubject->Notify(Observer::Event::UISubmit);
				return true;
			});
		easyModeButton->SetCancelCallback([this]()
			{
				return false;
			});

		// ハードモード選択ボタン
		auto hardModeButton = bg->CreateToChild<UI::MenuItem>();
		hardModeButton->GetRectTransform()->localPosition = kHardModeTextPos;
		hardModeButton->GetRectTransform()->SetFullRectAsFixed(kButtonRect);
		hardModeButton->GetRectTransform()->SetAnchor(RectTransform::Anchor::RightBottom);

		UI::TextObject* hardModeText = hardModeButton->CreateToChild<UI::TextObject>(font, kHardModeText, Color::white, HolizontalAlignment::Center, VerticalAlignment::Middle);
		hardModeText->GetRectTransform()->SetAnchor(RectTransform::Anchor::FullStretch);

		hardModeButton->SetSelectCallback([hardModeText, this]()
			{
				hardModeText->SetColor(Color::green);
				mEventSubject->Notify(Observer::Event::UIMoveCursor);
			});
		hardModeButton->SetDeselectCallback([hardModeText]() { hardModeText->SetColor(Color::white); });
		hardModeButton->SetSubmitCallback([this]()
			{
				this->SetCommand(Command::StartHardMode);
				mEventSubject->Notify(Observer::Event::UISubmit);
				return true;
			});
		hardModeButton->SetCancelCallback([this]()
			{
				return false;
			});

		AddMenuItem(easyModeButton);
		AddMenuItem(hardModeButton);

		const SaveData& saveData = UserDataManager::GetInstance().GetSaveData();
		if (saveData.easyHighscore != 0 || saveData.hardHighscore != 0)
		{
			UI::TextObject* highscoreDescText = bg->CreateToChild<UI::TextObject>(fontSmall, kHighscoreDescText, Color::yellow, HolizontalAlignment::Center, VerticalAlignment::Middle);
			highscoreDescText->GetRectTransform()->localPosition = kHighscoreDescPos;

			UI::TextObject* easyHighscore = easyModeButton->CreateToChild<UI::TextObject>(fontSmall, std::to_string(saveData.easyHighscore), Color::yellow, HolizontalAlignment::Center, VerticalAlignment::Middle);
			easyHighscore->GetRectTransform()->localPosition = kHighscorePos;

			UI::TextObject* hardHighscore = hardModeButton->CreateToChild<UI::TextObject>(fontSmall, std::to_string(saveData.hardHighscore), Color::yellow, HolizontalAlignment::Center, VerticalAlignment::Middle);
			hardHighscore->GetRectTransform()->localPosition = kHighscorePos;
		}
	}

	void DifficultyMenuScreen::Init()
	{
	}

	void DifficultyMenuScreen::Update()
	{
	}

	void DifficultyMenuScreen::Setup()
	{
		MenuScreen::Setup();
	}

	bool DifficultyMenuScreen::ProcessInput(const Input::UIInputState& input)
	{
		if (input.left)
		{
			MoveCursorPrev();
		}
		if (input.right)
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
