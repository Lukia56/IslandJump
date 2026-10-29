#include "CloudInvasionEffect.h"
#include "System/Resource/ResourceBase.h"
#include "World/Component/Rendering/UIImageRenderer.h"

namespace
{
	constexpr float kDampingDistance = 800.0f;
}

namespace UI
{
	CloudInvasionEffect::CloudInvasionEffect(std::shared_ptr<Resource::ResourceBase> texture, Transform* playerTransform, Transform* cloudTransform) :
		mPlayerTransform(playerTransform),
		mCloudTransform(cloudTransform),
		mRenderer(nullptr)
	{
		mRectTransform->SetAnchor(RectTransform::Anchor::FullStretch);

		mRenderer = std::make_unique<UIImageRenderer>(this, texture, mRectTransform);
	}

	void CloudInvasionEffect::Init()
	{
	}

	void CloudInvasionEffect::Update()
	{
		float distance = mPlayerTransform->CalculateWorldPosition().y - mCloudTransform->CalculateWorldPosition().y;

		mRenderer->SetAlpha(1.0f - distance / kDampingDistance);
	}

	void CloudInvasionEffect::Draw()
	{
		mRenderer->Draw();
	}
}
