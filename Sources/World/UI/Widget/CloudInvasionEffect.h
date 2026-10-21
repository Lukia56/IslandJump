#pragma once

#include "../Core/UIObject.h"

class UIImageRenderer;
namespace Resource
{
	class ResourceBase;
}

namespace UI
{
	class CloudInvasionEffect : public UIObject
	{
	public:

		CloudInvasionEffect(std::shared_ptr<Resource::ResourceBase> texture, Transform* playerTransform, Transform* cloudTransform);
		~CloudInvasionEffect() = default;

		void Init() override;

		void Update() override;

		void Draw() override;

	private:

		Transform* mPlayerTransform;

		Transform* mCloudTransform;

		std::unique_ptr<UIImageRenderer> mRenderer;
	};
}
