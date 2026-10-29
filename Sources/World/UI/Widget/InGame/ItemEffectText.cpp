#include "ItemEffectText.h"
#include "../TextObject.h"
#include "System/TimeManager.h"
#include "Utility/Color.h"

namespace
{
	constexpr float kMoveSpeed = -100.0f;
	constexpr float kFadeSpeed = 1.0f;

	constexpr float kStartAlpha = 2.0f;

	std::string kEffectTexts[] = {
		"ジャンプ力上昇！",
		"移動速度上昇！",
		"空中制御力上昇！"
	};

	Color kEffectColors[] = {
		Color{ 0.219f, 0.87f,  0.384f },
		Color{ 0.019f, 0.811f, 0.968f },
		Color{ 0.968f, 0.364f, 0.431f }
	};
}

namespace UI
{
	ItemEffectText::ItemEffectText(std::shared_ptr<Resource::ResourceBase> font) :
		mAlpha(0.0f),
		mText(nullptr)
	{
		mText = CreateToChild<UI::TextObject>(font, "", Color::white);
	}

	void ItemEffectText::Init()
	{
	}

	void ItemEffectText::Update()
	{
		if (mAlpha > 0.0f)
		{
			mTransform->Translate(0.0f, kMoveSpeed * TimeManager::GetDeltaTime(), 0.0f);

			Color color = mText->GetColor();
			mAlpha -= kFadeSpeed * TimeManager::GetDeltaTime();
			color.a = mAlpha;
			mText->SetColor(color);
		}
	}

	void ItemEffectText::Setup(ItemType itemType)
	{
		int type = static_cast<int>(itemType);

		mText->SetDisplayText(kEffectTexts[type]);
		mText->SetColor(kEffectColors[type]);

		mAlpha = kStartAlpha;
	}
}
