#include "TitleMenuScreen.h"
#include "../Core/UIRoot.h"
#include "../Widget/ImageObject.h"
#include "../Widget/MenuItem.h"
#include "../Widget/TextObject.h"
#include "Observer/Subject.h"
#include "System/ResourceManager.h"
#include "System/Input/Literal/InputState.h"
#include "System/Resource/Font.h"
#include "System/Resource/Texture.h"

namespace
{
	const char* const kStartText = "ゲーム開始";
	const char* const kOptionsText = "設定";
	const char* const kQuitText = "ゲーム終了";

	constexpr Vector3 kLogoSpritePos{ 0.0f, -100.0f, 0.0f };
	constexpr Vector3 kStartTextPos{ 0.0f, 250.0f, 0.0f };
	constexpr Vector3 kOptionsTextPos{ 0.0f, 350.0f, 0.0f };
	constexpr Vector3 kQuitTextPos{ 0.0f, 450.0f, 0.0f };

	constexpr Vector2 kButtonRect{ 160.0f, 32.0f };

	const char* const kFontPath = "Resources\\Font\\Nicokaku.dft";

	const char* const kLogoSpritePath = "Resources\\Sprite\\Logo.png";
}

namespace UI
{
	TitleMenuScreen::TitleMenuScreen() :
		mEventSubject(nullptr)
	{
		mEventSubject = std::make_unique<Observer::Subject>();

		// プッシュ時に項目オブジェクトが無いと初期選択がされないため、コンストラクタで生成

		UI::UIRoot* itemRoot = GetMenuItemRoot();

		std::shared_ptr<Resource::ResourceBase> logoSprite = ResourceManager::GetInstance().GetResource<Resource::Texture>(kLogoSpritePath);
		std::shared_ptr<Resource::ResourceBase> font = ResourceManager::GetInstance().GetResource<Resource::Font>(kFontPath);

		// タイトルロゴ
		auto titleLogo = itemRoot->CreateToChild<UI::ImageObject>(logoSprite);
		titleLogo->GetRectTransform()->localPosition = kLogoSpritePos;

		// 開始ボタン
		auto startButton = itemRoot->CreateToChild<UI::MenuItem>();
		startButton->GetRectTransform()->localPosition = kStartTextPos;
		startButton->GetRectTransform()->SetFullRectAsFixed(kButtonRect);

		UI::TextObject* startText = startButton->CreateToChild<UI::TextObject>(font, kStartText, Color::white, HolizontalAlignment::Center, VerticalAlignment::Middle);
		startText->GetRectTransform()->SetAnchor(RectTransform::Anchor::FullStretch);

		startButton->SetSelectCallback([startText, this]()
			{
				startText->SetColor(Color::green);
				mEventSubject->Notify(Observer::Event::UIMoveCursor);
			});
		startButton->SetDeselectCallback([startText]() { startText->SetColor(Color::white); });
		startButton->SetSubmitCallback([this]()
			{
				this->SetCommand(Command::StartGame);
				mEventSubject->Notify(Observer::Event::UISubmit);
				return true;
			});

		// 設定ボタン
		auto optionsButton = itemRoot->CreateToChild<UI::MenuItem>();
		optionsButton->GetRectTransform()->localPosition = kOptionsTextPos;
		optionsButton->GetRectTransform()->SetFullRectAsFixed(kButtonRect);

		UI::TextObject* optionsText = optionsButton->CreateToChild<UI::TextObject>(font, kOptionsText, Color::white, HolizontalAlignment::Center, VerticalAlignment::Middle);
		optionsText->GetRectTransform()->SetAnchor(RectTransform::Anchor::FullStretch);

		optionsButton->SetSelectCallback([optionsText, this]()
			{
				optionsText->SetColor(Color::green);
				mEventSubject->Notify(Observer::Event::UIMoveCursor);
			});
		optionsButton->SetDeselectCallback([optionsText]() { optionsText->SetColor(Color::white); });
		optionsButton->SetSubmitCallback([this]()
			{
				this->SetCommand(Command::OpenOptions);
				mEventSubject->Notify(Observer::Event::UISubmit);
				return true;
			});

		// 終了ボタン
		auto quitButton = itemRoot->CreateToChild<UI::MenuItem>();
		quitButton->GetRectTransform()->localPosition = kQuitTextPos;
		quitButton->GetRectTransform()->SetFullRectAsFixed(kButtonRect);

		UI::TextObject* quitText = quitButton->CreateToChild<UI::TextObject>(font, kQuitText, Color::white, HolizontalAlignment::Center, VerticalAlignment::Middle);
		quitText->GetRectTransform()->SetAnchor(RectTransform::Anchor::FullStretch);

		quitButton->SetSelectCallback([quitText, this]()
			{
				quitText->SetColor(Color::green);
				mEventSubject->Notify(Observer::Event::UIMoveCursor);
			});
		quitButton->SetDeselectCallback([quitText]() { quitText->SetColor(Color::white); });
		quitButton->SetSubmitCallback([this]()
			{
				this->SetCommand(Command::QuitGame);
				mEventSubject->Notify(Observer::Event::UISubmit);
				return true;
			});

		AddMenuItem(startButton);
		AddMenuItem(optionsButton);
		AddMenuItem(quitButton);
	}

	void TitleMenuScreen::Init()
	{
	}

	void TitleMenuScreen::Update()
	{
	}

	void TitleMenuScreen::Draw()
	{
	}

	void TitleMenuScreen::Setup()
	{
		MenuScreen::Setup();
	}

	bool TitleMenuScreen::ProcessInput(const Input::UIInputState& input)
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
