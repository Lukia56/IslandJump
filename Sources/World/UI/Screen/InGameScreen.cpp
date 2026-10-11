#include "InGameScreen.h"
#include "../Core/UIRoot.h"
#include "../Widget/GoalProgressBar.h"

namespace
{
	constexpr Vector3 kGoalProgressBarPos{ -100.0f, 0.0f, 0.0f };
}

namespace UI
{
	InGameScreen::InGameScreen(float maxDistance, Transform* playerTransform)
	{
		UI::GoalProgressBar* goalProgressBar = CreateToChild<UI::GoalProgressBar>(maxDistance, playerTransform);
		goalProgressBar->GetRectTransform()->localPosition = kGoalProgressBarPos;
		goalProgressBar->GetRectTransform()->SetAnchor(RectTransform::Anchor::RightMiddle);
	}

	void InGameScreen::Init()
	{
	}

	void InGameScreen::Update()
	{
	}
}
