#include "SceneEffectTest.h"
#include "System/InputManager.h"
#include "System/ResourceManager.h"
#include "System/Resource/Effect.h"
#include "World/Other/EffectManager.h"

namespace
{
	constexpr int kMaxEffectNum = 100;

	constexpr Vector3 kEffectPos{ 0.0f, 100.0f, -400.0f };

	const char* const kEffectPath = "Resources\\Effect\\ItemConsumeEffect_JumpBoost.efk";
}

SceneEffectTest::SceneEffectTest() :
	mEffectManager(nullptr)
{
}

void SceneEffectTest::OnInit()
{
	mEffectManager = CreateToRoot<EffectManager>(kMaxEffectNum);
	mEffectManager->RegisterEffect(ResourceManager::GetInstance().GetResource<Resource::Effect>(kEffectPath));
}

std::unique_ptr<SceneBase> SceneEffectTest::OnUpdate()
{
	if (InputManager::GetInstance().IsPressed(Input::Action::Submit))
	{
		mEffectManager->Play(kEffectPath, kEffectPos);
	}

	return nullptr;
}
