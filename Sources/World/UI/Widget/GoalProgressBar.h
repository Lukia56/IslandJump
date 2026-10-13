#pragma once

#include "../Core/UIObject.h"

namespace Resource
{
	class ResourceBase;
}

namespace UI
{
	class BoxObject;
	class TextObject;

	class GoalProgressBar : public UIObject
	{
	public:

		GoalProgressBar(float maxDistance, Transform* playerTransform, std::shared_ptr<Resource::ResourceBase> font);
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
