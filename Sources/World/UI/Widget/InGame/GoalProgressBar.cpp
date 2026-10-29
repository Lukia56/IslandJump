#include "GoalProgressBar.h"
#include "../BoxObject.h"
#include "../TextObject.h"
#include "System/Resource/ResourceBase.h"

namespace
{
	constexpr Vector3 kBoxPos{ 0.0f, 300.0f, 0.0f };
	constexpr Vector2 kBoxSize{ 50.0f, 600.0f };

	constexpr Vector3 kProgressPos{ 0.0f, 300.0f, 0.0f };

	const char* const kProgressTextPrefix = "ÉSÅ[ÉãÇ‹Ç≈Ç†Ç∆";
	const char* const kProgressTextPostFix = "m";
}

namespace UI
{
	GoalProgressBar::GoalProgressBar(float maxDistance, Transform* playerTransform, Transform* cloudTransform, std::shared_ptr<Resource::ResourceBase> font) :
		mMaxDistance(maxDistance),
		mCurrentDistance(0.0f),
		mPlayerTransform(playerTransform),
		mCloudTransform(cloudTransform),
		mMaxBar(nullptr),
		mCurrentBar(nullptr),
		mCloudBar(nullptr),
		mProgressText(nullptr)
	{
		mProgressText = CreateToChild<UI::TextObject>(font, "", Color::white, HolizontalAlignment::Right);
		mProgressText->GetRectTransform()->localPosition = kProgressPos;
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

		mCloudBar = CreateToChild<UI::BoxObject>(Color::gray);
		mCloudBar->GetRectTransform()->localPosition = kBoxPos;
		mCloudBar->GetRectTransform()->SetFullRectAsFixed(kBoxSize);
		mCloudBar->GetRectTransform()->SetPivot(Vector2(0.0f, 1.0f));
	}

	void GoalProgressBar::Update()
	{
		mCurrentDistance = Math::Max(mCurrentDistance, mPlayerTransform->CalculateWorldPosition().y);
		float progressRate = Math::Clamp(mCurrentDistance / mMaxDistance, 0.0f, 1.0f);
		mCurrentBar->GetRectTransform()->SetRectHeightAsFixed(kBoxSize.y * progressRate);

		float cloudPosRate = Math::Clamp(mCloudTransform->CalculateWorldPosition().y / mMaxDistance, 0.0f, 1.0f);
		mCloudBar->GetRectTransform()->SetRectHeightAsFixed(kBoxSize.y * cloudPosRate);

		float distance = mMaxDistance - mPlayerTransform->CalculateWorldPosition().y;
		int clampedDistance = Math::Max(static_cast<int>(distance), 0);
		mProgressText->SetDisplayText(kProgressTextPrefix + std::to_string(clampedDistance) + kProgressTextPostFix);
		mProgressText->GetRectTransform()->localPosition.y = kProgressPos.y + -kBoxSize.y * progressRate;
	}
}
