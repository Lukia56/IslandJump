#pragma once

#include "../SceneBase.h"

class EffectManager;

class SceneEffectTest : public SceneBase
{
public:

	SceneEffectTest();
	~SceneEffectTest() = default;

	void OnInit() override;

	std::unique_ptr<SceneBase> OnUpdate() override;

private:

	EffectManager* mEffectManager;
};
