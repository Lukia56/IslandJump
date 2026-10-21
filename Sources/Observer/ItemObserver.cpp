#include "ItemObserver.h"
#include <string>
#include "World/Other/EffectInstance.h"
#include "World/Other/EffectManager.h"

namespace
{
	std::string kEffectPaths[] = {
		"Resources\\Effect\\ItemConsumeEffect_JumpBoost.efk",
		"Resources\\Effect\\ItemConsumeEffect_SpeedBoost.efk",
		"Resources\\Effect\\ItemConsumeEffect_AerialControl.efk"
	};
}

namespace Observer
{
	ItemObserver::ItemObserver(Transform* playerTransform, EffectManager* effectManager) :
		mPlayerTransform(playerTransform),
		mEffectManager(effectManager)
	{
	}

	void ItemObserver::OnNotify(Event event, int value)
	{
		if (event != Event::ItemObtain) return;

		GameObject* effectInstance = mEffectManager->Play(kEffectPaths[value], Vector3::Zero);
		effectInstance->GetTransform()->ChangeParent(mPlayerTransform);
	}
}
