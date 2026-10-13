#include "DifficultyMenuScreen.h"
#include "../Core/UIRoot.h"
#include "../Widget/BoxObject.h"
#include "../Widget/MenuItem.h"
#include "../Widget/TextObject.h"
#include "Observer/Subject.h"
#include "System/ResourceManager.h"
#include "System/Input/Literal/InputState.h"
#include "System/Resource/Font.h"

namespace
{
	const char* const kDescText = "Choose difficulty";

	constexpr Vector3 kDescPos{ 0.0f, -300.0f, 0.0f };
	constexpr Vector2 kDescRect{ 200.0f, 32.0f };

	const char* const kEasyModeText = "Easy";
	constexpr Vector3 kEasyModeTextPos{ -250.0f, -150.0f, 0.0f };

	const char* const kHardModeText = "Hard";
	constexpr Vector3 kHardModeTextPos{ 250.0f, -150.0f, 0.0f };

	constexpr Vector2 kButtonRect{ 160.0f, 32.0f };

	constexpr Vector3 kBackgroundPos{ 0.0f, 0.0f, 0.0f };
	constexpr Vector2 kBackgroundRect{ 800.0f, 750.0f };

	const char* const kFontPath = "Resources\\Font\\ShowcardGothic.dft";
}

namespace UI
{
	DifficultyMenuScreen::DifficultyMenuScreen()
	{
		mEventSubject = std::make_unique<Observer::Subject>();

		// プッシュ時に項目オブジェクトが無いと初期選択がされないため、コンストラクタで生成

		BoxObject* bg = CreateToChild<UI::BoxObject>(Color{ 0.0f, 0.0f, 0.0f, 0.5f });
		bg->GetRectTransform()->localPosition = kBackgroundPos;
		bg->GetRectTransform()->SetFullRectAsFixed(kBackgroundRect);

		std::shared_ptr<Resource::ResourceBase> font = ResourceManager::GetInstance().GetResource<Resource::Font>(kFontPath);

		TextObject* descText = CreateToChild<UI::TextObject>(font, kDescText, Color::white, HolizontalAlignment::Center, VerticalAlignment::Middle);
		descText->GetRectTransform()->localPosition = kDescPos;
		descText->GetRectTransform()->SetFullRectAsFixed(kDescRect);

		// イージーモード選択ボタン
		auto easyModeButton = CreateToChild<UI::MenuItem>();
		easyModeButton->GetRectTransform()->localPosition = kEasyModeTextPos;
		easyModeButton->GetRectTransform()->SetFullRectAsFixed(kButtonRect);

		UI::TextObject* easyModeText = easyModeButton->CreateToChild<UI::TextObject>(font, kEasyModeText, Color::white, HolizontalAlignment::Center, VerticalAlignment::Middle);
		easyModeText->GetRectTransform()->SetAnchor(RectTransform::Anchor::FullStretch);

		easyModeButton->SetSelectCallback([easyModeText, this]()
			{
				easyModeText->SetColor(Color::cyan);
				mEventSubject->Notify(Observer::Event::UIMoveCursor);
			});
		easyModeButton->SetDeselectCallback([easyModeText]() { easyModeText->SetColor(Color::white); });
		easyModeButton->SetSubmitCallback([this]()
			{
				this->SetCommand(Command::StartEasyMode);
				mEventSubject->Notify(Observer::Event::UISubmit);
				return true;
			});

		// ハードモード選択ボタン
		auto hardModeButton = CreateToChild<UI::MenuItem>();
		hardModeButton->GetRectTransform()->localPosition = kHardModeTextPos;
		hardModeButton->GetRectTransform()->SetFullRectAsFixed(kButtonRect);

		UI::TextObject* hardModeText = hardModeButton->CreateToChild<UI::TextObject>(font, kHardModeText, Color::white, HolizontalAlignment::Center, VerticalAlignment::Middle);
		hardModeText->GetRectTransform()->SetAnchor(RectTransform::Anchor::FullStretch);

		hardModeButton->SetSelectCallback([hardModeText, this]()
			{
				hardModeText->SetColor(Color::cyan);
				mEventSubject->Notify(Observer::Event::UIMoveCursor);
			});
		hardModeButton->SetDeselectCallback([hardModeText]() { hardModeText->SetColor(Color::white); });
		hardModeButton->SetSubmitCallback([this]()
			{
				this->SetCommand(Command::StartHardMode);
				mEventSubject->Notify(Observer::Event::UISubmit);
				return true;
			});

		AddMenuItem(easyModeButton);
		AddMenuItem(hardModeButton);
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

		return true;
	}
}
