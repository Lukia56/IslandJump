#include "BillboardRenderer.h"
#include <DxLib.h>
#include "System/Resource/ResourceBase.h"
#include "World/GameObject.h"

BillboardRenderer::BillboardRenderer(GameObject* owner, std::shared_ptr<Resource::ResourceBase> resource) :
	Renderer(owner, resource),
	mTexWidth(0.0f)
{
	if (resource)
	{
		// 画像のサイズを取得
		float height;
		GetGraphSizeF(resource->GetHandle(), &mTexWidth, &height);
	}
}

void BillboardRenderer::Draw() const
{
	if (!mOwner) return;
	if (!mResource) return;

	const VECTOR pos = (mOwner->GetTransform()->CalculateWorldPosition() + mOffsetPos).GetAsDxLibVector();
	const VECTOR rot = mOwner->GetTransform()->CalculateWorldRotation().GetAsDxLibVector();
	const VECTOR scale = mOwner->GetTransform()->CalculateWorldScale().GetAsDxLibVector();

	DrawBillboard3D(pos, 0.5f, 0.5f, mTexWidth * scale.x, rot.z, mResource->GetHandle(), true);
}

void BillboardRenderer::SetResource(std::shared_ptr<Resource::ResourceBase> resource)
{
	Renderer::SetResource(resource);

	if (resource)
	{
		// 画像のサイズを取得
		float height;
		GetGraphSizeF(resource->GetHandle(), &mTexWidth, &height);
	}
}
