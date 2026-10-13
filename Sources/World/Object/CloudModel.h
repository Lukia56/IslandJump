#pragma once

#include "../GameObject.h"

class ModelRenderer;
namespace Resource
{
	class ResourceBase;
}

class CloudModel : public GameObject
{
public:

	CloudModel(std::shared_ptr<Resource::ResourceBase> model);
	~CloudModel() = default;

	void Init() override;

	void Update() override;

	void Draw() override;

private:

	std::unique_ptr<ModelRenderer> mModel;
};
