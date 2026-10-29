#pragma once

#include "World/UI/Core/UIObject.h"

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

		GoalProgressBar(float maxDistance, Transform* playerTransform, Transform* cloudTransform, std::shared_ptr<Resource::ResourceBase> font);
		~GoalProgressBar() = default;

		void Init() override;

		void Update() override;

	private:

		float mMaxDistance;

		float mCurrentDistance;

		Transform* mPlayerTransform;

		Transform* mCloudTransform;

		BoxObject* mMaxBar;

		BoxObject* mCurrentBar;

		BoxObject* mCloudBar;

		TextObject* mProgressText;
	};
}
