#pragma once

#include "../SceneBase.h"

class SceneLoadStageTest : public SceneBase
{
public:

	SceneLoadStageTest();
	~SceneLoadStageTest() = default;

	void OnInit() override;

	std::unique_ptr<SceneBase> OnUpdate() override;
};
