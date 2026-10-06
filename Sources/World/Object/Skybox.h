#pragma once

#include "../GameObject.h"

class ModelRenderer;
namespace Resource
{
	class ResourceBase;
}

class Skybox : public GameObject
{
public:

	Skybox(std::shared_ptr<Resource::ResourceBase> model);
	~Skybox() = default;

	void Init() override;

	void Update() override;

	void Draw() override;

private:

	std::unique_ptr<ModelRenderer> mModel;
};
