#include "ItemObserver.h"
#include <string>
#include "World/Other/Effect/EffectInstance.h"
#include "World/Other/Effect/EffectManager.h"
#include "World/UI/Widget/ItemEffectTextManager.h"

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
	ItemObserver::ItemObserver(Transform* playerTransform, EffectManager* effectManager, UI::ItemEffectTextManager* itemEffectTextManager) :
		mPlayerTransform(playerTransform),
		mEffectManager(effectManager),
		mItemEffectTextManager(itemEffectTextManager)
	{
	}

	void ItemObserver::OnNotify(Event event, int value)
	{
		if (event != Event::ItemObtain) return;

		GameObject* effectInstance = mEffectManager->Play(kEffectPaths[value], Vector3::Zero);
		effectInstance->GetTransform()->ChangeParent(mPlayerTransform);

		mItemEffectTextManager->Create(static_cast<ItemType>(value));
	}
}
