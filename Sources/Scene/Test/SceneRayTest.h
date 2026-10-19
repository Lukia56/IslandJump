#pragma once

#include "../SceneBase.h"

class SceneRayTest : public SceneBase
{
public:

	SceneRayTest();
	~SceneRayTest() = default;

	void OnInit() override;

	std::unique_ptr<SceneBase> OnUpdate() override;

private:


};
