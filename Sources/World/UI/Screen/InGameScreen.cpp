#include "InGameScreen.h"
#include "../Widget/CloudInvasionEffect.h"
#include "../Widget/GoalProgressBar.h"
#include "../Widget/ItemUseCountUI.h"
#include "../Widget/ItemEffectTextManager.h"
#include "System/ResourceManager.h"
#include "System/Resource/Font.h"
#include "System/Resource/Texture.h"
#include "World/Other/ItemObjectManager.h"
#include "World/Other/ResultRecorder.h"

namespace
{
	constexpr Vector3 kGoalProgressBarPos{ -100.0f, 0.0f, 0.0f };

	constexpr Vector3 kJumpBoostPos{ -200.0f, -75.0f, 0.0f };
	constexpr Vector3 kSpeedBoostPos{ 0.0f, -75.0f, 0.0f };
	constexpr Vector3 kAerialControlPos{ 200.0f, -75.0f, 0.0f };

	constexpr int kItemEffectTextNum = 10;

	const char* const kFontPath = "Resources\\Font\\ShowcardGothic.dft";
	const char* const kCloudInvasionEffectTexturePath = "Resources\\Sprite\\InvasionEffect.png";
}

namespace UI
{
	InGameScreen::InGameScreen(float maxDistance, Transform* playerTransform, Transform* cloudTransform, ItemObjectManager* itemObjectManager, ResultRecorder* resultRecorder)
	{
		std::shared_ptr<Resource::ResourceBase> font = ResourceManager::GetInstance().GetResource<Resource::Font>(kFontPath);

		UI::GoalProgressBar* goalProgressBar = CreateToChild<UI::GoalProgressBar>(maxDistance, playerTransform, cloudTransform, font);
		goalProgressBar->GetRectTransform()->localPosition = kGoalProgressBarPos;
		goalProgressBar->GetRectTransform()->SetAnchor(RectTransform::Anchor::RightMiddle);

		UI::ItemUseCountUI* jumpBoost = CreateToChild<UI::ItemUseCountUI>(ItemType::JumpBoost, itemObjectManager, font);
		jumpBoost->GetRectTransform()->localPosition = kJumpBoostPos;
		jumpBoost->GetRectTransform()->SetAnchor(RectTransform::Anchor::CenterBottom);

		UI::ItemUseCountUI* speedBoost = CreateToChild<UI::ItemUseCountUI>(ItemType::SpeedUp, itemObjectManager, font);
		speedBoost->GetRectTransform()->localPosition = kSpeedBoostPos;
		speedBoost->GetRectTransform()->SetAnchor(RectTransform::Anchor::CenterBottom);

		UI::ItemUseCountUI* aerialControl = CreateToChild<UI::ItemUseCountUI>(ItemType::AerialControl, itemObjectManager, font);
		aerialControl->GetRectTransform()->localPosition = kAerialControlPos;
		aerialControl->GetRectTransform()->SetAnchor(RectTransform::Anchor::CenterBottom);

		std::shared_ptr<Resource::ResourceBase> cloudInvasionEffectTexture = ResourceManager::GetInstance().GetResource<Resource::Texture>(kCloudInvasionEffectTexturePath);

		CreateToChild<UI::CloudInvasionEffect>(cloudInvasionEffectTexture, playerTransform, cloudTransform);

		mItemEffectTextManager = CreateToChild<UI::ItemEffectTextManager>(font, kItemEffectTextNum);
	}

	void InGameScreen::Init()
	{
	}

	void InGameScreen::Update()
	{
	}
}
