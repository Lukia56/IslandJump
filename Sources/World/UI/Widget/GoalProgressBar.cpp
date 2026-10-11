#include "GoalProgressBar.h"
#include "BoxObject.h"
#include "TextObject.h"
#include "System/ResourceManager.h"
#include "System/Resource/Font.h"

namespace
{
	constexpr Vector3 kBoxPos{ 0.0f, 300.0f, 0.0f };
	constexpr Vector2 kBoxSize{ 50.0f, 600.0f };

	constexpr Vector3 kProgressPos{ 0.0f, 300.0f, 0.0f };

	const char* const kProgressText = "m to goal";

	const char* const kFontPath = "Resources\\Font\\ShowcardGothic.dft";
}

namespace UI
{
	GoalProgressBar::GoalProgressBar(float maxDistance, Transform* playerTransform) :
		mMaxDistance(maxDistance),
		mPlayerTransform(playerTransform),
		mMaxBar(nullptr),
		mCurrentBar(nullptr),
		mProgressText(nullptr)
	{
	}

	void GoalProgressBar::Init()
	{
		mMaxBar = CreateToChild<UI::BoxObject>(Color::black);
		mMaxBar->GetRectTransform()->localPosition = kBoxPos;
		mMaxBar->GetRectTransform()->SetFullRectAsFixed(kBoxSize);
		mMaxBar->GetRectTransform()->SetPivot(Vector2(0.0f, 1.0f));

		mCurrentBar = CreateToChild<UI::BoxObject>(Color::green);
		mCurrentBar->GetRectTransform()->localPosition = kBoxPos;
		mCurrentBar->GetRectTransform()->SetFullRectAsFixed(kBoxSize);
		mCurrentBar->GetRectTransform()->SetPivot(Vector2(0.0f, 1.0f));

		std::shared_ptr<Resource::ResourceBase> font = ResourceManager::GetInstance().GetResource<Resource::Font>(kFontPath);
		mProgressText = CreateToChild<UI::TextObject>(font, kProgressText, Color::white, HolizontalAlignment::Right);
		mProgressText->GetRectTransform()->localPosition = kProgressPos;
	}

	void GoalProgressBar::Update()
	{
		float progressRate = Math::Clamp(mPlayerTransform->CalculateWorldPosition().y / mMaxDistance, 0.0f, 1.0f);

		mCurrentBar->GetRectTransform()->SetRectHeightAsFixed(kBoxSize.y * progressRate);

		mProgressText->SetDisplayText(std::to_string(static_cast<int>(mMaxDistance - mPlayerTransform->CalculateWorldPosition().y)) + kProgressText);
		mProgressText->GetRectTransform()->localPosition.y = kProgressPos.y + -kBoxSize.y * progressRate;
	}
}
