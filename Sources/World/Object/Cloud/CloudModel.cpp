#include "CloudModel.h"
#include "World/Component/Rendering/ModelRenderer.h"

CloudModel::CloudModel(std::shared_ptr<Resource::ResourceBase> model)
{
	mModel = std::make_unique<ModelRenderer>(this, model);
}

void CloudModel::Init()
{
}

void CloudModel::Update()
{
}

void CloudModel::Draw()
{
	mModel->Draw();
}
