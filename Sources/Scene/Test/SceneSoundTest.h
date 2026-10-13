#pragma once

#include "../SceneBase.h"

namespace Resource
{
	class ResourceBase;
}

class SceneSoundTest : public SceneBase
{
public:

	SceneSoundTest();
	~SceneSoundTest() = default;

	void OnInit() override;

	std::unique_ptr<SceneBase> OnUpdate() override;

private:

	std::shared_ptr<Resource::ResourceBase> mSound;
};
