#include "OptionsMenuScreen.h"
#include "../Core/UIRoot.h"
#include "../Widget/BoxObject.h"
#include "../Widget/MenuItem.h"
#include "../Widget/TextObject.h"
#include "System/ResourceManager.h"
#include "System/UserDataManager.h"
#include "System/Input/Literal/InputState.h"
#include "System/Resource/Font.h"

namespace
{
	const char* const kExitText = "Exit";
	const char* const kMouseSensitivityXText = "Mouse Sensitivity X";
	const char* const kMouseSensitivityYText = "Mouse Sensitivity Y";

	constexpr Vector3 kExitTextPos{ 25.0f, 100.0f, 0.0f };
	constexpr Vector3 kMouseSensitivityXTextPos{ 25.0f, 200.0f, 0.0f };
	constexpr Vector3 kMouseSensitivityYTextPos{ 25.0f, 300.0f, 0.0f };

	constexpr Vector3 kMouseSensitivityXValueTextPos{ -200.0f, 200.0f, 0.0f };
	constexpr Vector3 kMouseSensitivityYValueTextPos{ -200.0f, 300.0f, 0.0f };

	constexpr Vector2 kButtonRect{ 160.0f, 32.0f };

	constexpr Vector2 kBackgroundRect{ 800.0f, 500.0f };

	const char* const kFontPath = "Resources\\Font\\ShowcardGothicSmall.dft";

	constexpr int kMaxSensitivity = 200;
	constexpr int kMinSensitivity = 50;

	constexpr int kSensitivityChange = 10;
}

namespace UI
{
	OptionsMenuScreen::OptionsMenuScreen() :
		mMouseSensitivityXValueText(nullptr),
		mMouseSensitivityYValueText(nullptr)
	{
	}

	void OptionsMenuScreen::Init()
	{
		BoxObject* bg = CreateToChild<UI::BoxObject>(Color(0.0f, 0.0f, 0.0f, 0.5f));
		bg->GetRectTransform()->SetFullRectAsFixed(kBackgroundRect);

		std::shared_ptr<Resource::ResourceBase> font = ResourceManager::GetInstance().GetResource<Resource::Font>(kFontPath);

		// 終了ボタン
		MenuItem* exitButton = bg->CreateToChild<UI::MenuItem>();
		{
			exitButton->GetRectTransform()->localPosition = kExitTextPos;
			exitButton->GetRectTransform()->SetAnchor(RectTransform::Anchor::LeftTop);

			UI::TextObject* exitText = exitButton->CreateToChild<UI::TextObject>(font, kExitText, Color::white, HolizontalAlignment::Left, VerticalAlignment::Middle);
			exitText->GetRectTransform()->SetAnchor(RectTransform::Anchor::FullStretch);

			exitButton->SetSelectCallback([exitText, this]()
				{
					exitText->SetColor(Color::green);
				});
			exitButton->SetDeselectCallback([exitText]() { exitText->SetColor(Color::white); });
			exitButton->SetSubmitCallback([this]()
				{
					this->SetCommand(Command::ExitOptions);
					return false;
				});
		}

		// 水平マウス感度設定ボタン
		MenuItem* mouseSnstvXButton = bg->CreateToChild<UI::MenuItem>();
		{
			mouseSnstvXButton->GetRectTransform()->localPosition = kMouseSensitivityXTextPos;
			mouseSnstvXButton->GetRectTransform()->SetAnchor(RectTransform::Anchor::LeftTop);

			mMouseSensitivityXValueText = bg->CreateToChild<UI::TextObject>(font, "", Color::white, HolizontalAlignment::Left, VerticalAlignment::Middle);
			mMouseSensitivityXValueText->GetRectTransform()->localPosition = kMouseSensitivityXValueTextPos;
			mMouseSensitivityXValueText->GetRectTransform()->SetAnchor(RectTransform::Anchor::RightTop);

			UI::TextObject* mouseSensitivityXText = mouseSnstvXButton->CreateToChild<UI::TextObject>(font, kMouseSensitivityXText, Color::white, HolizontalAlignment::Left, VerticalAlignment::Middle);
			mouseSensitivityXText->GetRectTransform()->SetAnchor(RectTransform::Anchor::FullStretch);

			mouseSnstvXButton->SetSelectCallback([mouseSensitivityXText, this]()
				{
					mouseSensitivityXText->SetColor(Color::green);
				});
			mouseSnstvXButton->SetDeselectCallback([mouseSensitivityXText]() { mouseSensitivityXText->SetColor(Color::white); });
			mouseSnstvXButton->SetPressLeftCallback([this]()
				{
					OptionsData& data = UserDataManager::GetInstance().GetTempOptionsData();
					data.mouseSensitivityX = Math::Max(data.mouseSensitivityX - kSensitivityChange, kMinSensitivity);
				});
			mouseSnstvXButton->SetPressRightCallback([this]()
				{
					OptionsData& data = UserDataManager::GetInstance().GetTempOptionsData();
					data.mouseSensitivityX = Math::Min(data.mouseSensitivityX + kSensitivityChange, kMaxSensitivity);
				});
		}

		// 垂直マウス感度設定ボタン
		MenuItem* mouseSnstvYButton = bg->CreateToChild<UI::MenuItem>();
		{
			mouseSnstvYButton->GetRectTransform()->localPosition = kMouseSensitivityYTextPos;
			mouseSnstvYButton->GetRectTransform()->SetAnchor(RectTransform::Anchor::LeftTop);

			mMouseSensitivityYValueText = bg->CreateToChild<UI::TextObject>(font, "", Color::white, HolizontalAlignment::Left, VerticalAlignment::Middle);
			mMouseSensitivityYValueText->GetRectTransform()->localPosition = kMouseSensitivityYValueTextPos;
			mMouseSensitivityYValueText->GetRectTransform()->SetAnchor(RectTransform::Anchor::RightTop);

			UI::TextObject* mouseSensitivityYText = mouseSnstvYButton->CreateToChild<UI::TextObject>(font, kMouseSensitivityYText, Color::white, HolizontalAlignment::Left, VerticalAlignment::Middle);
			mouseSensitivityYText->GetRectTransform()->SetAnchor(RectTransform::Anchor::FullStretch);

			mouseSnstvYButton->SetSelectCallback([mouseSensitivityYText, this]()
				{
					mouseSensitivityYText->SetColor(Color::green);
				});
			mouseSnstvYButton->SetDeselectCallback([mouseSensitivityYText]() { mouseSensitivityYText->SetColor(Color::white); });
			mouseSnstvYButton->SetPressLeftCallback([this]()
				{
					OptionsData& data = UserDataManager::GetInstance().GetTempOptionsData();
					data.mouseSensitivityY = Math::Max(data.mouseSensitivityY - kSensitivityChange, kMinSensitivity);
				});
			mouseSnstvYButton->SetPressRightCallback([this]()
				{
					OptionsData& data = UserDataManager::GetInstance().GetTempOptionsData();
					data.mouseSensitivityY = Math::Min(data.mouseSensitivityY + kSensitivityChange, kMaxSensitivity);
				});
		}

		AddMenuItem(exitButton);
		AddMenuItem(mouseSnstvXButton);
		AddMenuItem(mouseSnstvYButton);
	}

	void OptionsMenuScreen::Update()
	{
		OptionsData& data = UserDataManager::GetInstance().GetTempOptionsData();

		mMouseSensitivityXValueText->SetDisplayText(std::to_string(data.mouseSensitivityX) + "%");
		mMouseSensitivityYValueText->SetDisplayText(std::to_string(data.mouseSensitivityY) + "%");
	}

	void OptionsMenuScreen::Draw()
	{
	}

	void OptionsMenuScreen::Setup()
	{
		MenuScreen::Setup();
	}

	bool OptionsMenuScreen::ProcessInput(const Input::UIInputState& input)
	{
		if (input.up)
		{
			MoveCursorPrev();
		}
		if (input.down)
		{
			MoveCursorNext();
		}
		if (input.left)
		{
			InvokePressLeft();
		}
		if (input.right)
		{
			InvokePressRight();
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
