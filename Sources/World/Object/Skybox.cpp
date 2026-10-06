#include "Skybox.h"
#include <DxLib.h>
#include "System/Resource/ResourceBase.h"
#include "World/Component/Rendering/ModelRenderer.h"

namespace
{
	constexpr Vector3 kScale{ 10.0f, 10.0f, 10.0f };
}

Skybox::Skybox(std::shared_ptr<Resource::ResourceBase> model) :
	mModel(nullptr)
{
	mModel = std::make_unique<ModelRenderer>(this, model);
	MV1SetUseZBuffer(mModel->GetHandle(), false);

	mTransform->localScale = kScale;
}

void Skybox::Init()
{

}

void Skybox::Update()
{

}

void Skybox::Draw()
{
	SetUseLighting(false);
	mModel->Draw();
	SetUseLighting(true);
}
