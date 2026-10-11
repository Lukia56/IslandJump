#include "TitleMenuScreen.h"
#include "../Core/UIRoot.h"
#include "../Widget/ImageObject.h"
#include "../Widget/MenuItem.h"
#include "../Widget/TextObject.h"
#include "System/ResourceManager.h"
#include "System/Input/Literal/InputState.h"
#include "System/Resource/Font.h"
#include "System/Resource/Texture.h"

namespace
{
	const char* const kStartText = "Start Game";
	const char* const kQuitText = "Quit";

	constexpr Vector3 kLogoSpritePos{ 0.0f, -100.0f, 0.0f };
	constexpr Vector3 kStartTextPos{ 0.0f, 300.0f, 0.0f };
	constexpr Vector3 kQuitTextPos{ 0.0f, 400.0f, 0.0f };

	constexpr Vector2 kButtonRect{ 160.0f, 32.0f };

	const char* const kFontPath = "Resources\\Font\\ShowcardGothic.dft";

	const char* const kLogoSpritePath = "Resources\\Sprite\\Logo.png";
}

namespace UI
{
	TitleMenuScreen::TitleMenuScreen()
	{
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

		startButton->SetSelectCallback([startText]() { startText->SetColor(Color::green); });
		startButton->SetDeselectCallback([startText]() { startText->SetColor(Color::white); });
		startButton->SetSubmitCallback([this]()
									  {
										  this->SetCommand(Command::StartGame);
										  return true;
									  });

		// 終了ボタン
		auto quitButton = itemRoot->CreateToChild<UI::MenuItem>();
		quitButton->GetRectTransform()->localPosition = kQuitTextPos;
		quitButton->GetRectTransform()->SetFullRectAsFixed(kButtonRect);

		UI::TextObject* quitText = quitButton->CreateToChild<UI::TextObject>(font, kQuitText, Color::white, HolizontalAlignment::Center, VerticalAlignment::Middle);
		quitText->GetRectTransform()->SetAnchor(RectTransform::Anchor::FullStretch);

		quitButton->SetSelectCallback([quitText]() { quitText->SetColor(Color::green); });
		quitButton->SetDeselectCallback([quitText]() { quitText->SetColor(Color::white); });
		quitButton->SetSubmitCallback([this]()
									  {
										  this->SetCommand(Command::QuitGame);
										  return true;
									  });

		AddMenuItem(startButton);
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
