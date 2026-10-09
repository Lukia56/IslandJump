#include "DifficultyMenuScreen.h"
#include "../Core/UIRoot.h"
#include "../Widget/BoxObject.h"
#include "../Widget/MenuItem.h"
#include "../Widget/TextObject.h"
#include "System/ResourceManager.h"
#include "System/Input/Literal/InputState.h"
#include "System/Resource/Font.h"

namespace
{
	const char* const kDescText = "Choose difficulty";

	constexpr Vector3 kDescPos{ 0.0f, -300.0f, 0.0f };
	constexpr Vector2 kDescRect{ 200.0f, 32.0f };

	constexpr Vector3 kBackgroundPos{ 0.0f, 0.0f, 0.0f };
	constexpr Vector2 kBackgroundRect{ 800.0f, 750.0f };

	const char* const kFontPath = "Resources\\Font\\ShowcardGothic.dft";
}

namespace UI
{
	DifficultyMenuScreen::DifficultyMenuScreen()
	{
		// プッシュ時に項目オブジェクトが無いと初期選択がされないため、コンストラクタで生成

		UI::UIRoot* itemRoot = GetMenuItemRoot();

		std::shared_ptr<Resource::ResourceBase> font = ResourceManager::GetInstance().GetResource<Resource::Font>(kFontPath);

		BoxObject* bg = itemRoot->CreateToChild<UI::BoxObject>(Color{ 0.0f, 0.0f, 0.0f, 0.5f });
		bg->GetRectTransform()->localPosition = kBackgroundPos;
		bg->GetRectTransform()->SetFullRectAsFixed(kBackgroundRect);

		TextObject* descText = itemRoot->CreateToChild<UI::TextObject>(font, kDescText, Color::white, HolizontalAlignment::Center, VerticalAlignment::Middle);
		descText->GetRectTransform()->localPosition = kDescPos;
		descText->GetRectTransform()->SetFullRectAsFixed(kDescRect);
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
		if (input.submit)
		{
			if (!InvokeSubmit()) return false;
		}

		return true;
	}
}
