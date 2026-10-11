#pragma once

#include "../Core/UIObject.h"

namespace UI
{
	class BoxObject;
	class TextObject;

	class GoalProgressBar : public UIObject
	{
	public:

		GoalProgressBar(float maxDistance, Transform* playerTransform);
		~GoalProgressBar() = default;

		void Init() override;

		void Update() override;

	private:

		float mMaxDistance;

		Transform* mPlayerTransform;

		BoxObject* mMaxBar;

		BoxObject* mCurrentBar;

		TextObject* mProgressText;
	};
}
