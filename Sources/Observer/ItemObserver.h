#pragma once

#include "IObserver.h"

class Transform;
class EffectManager;
namespace UI
{
	class ItemEffectTextManager;
}

namespace Observer
{
	class ItemObserver : public IObserver
	{
	public:

		ItemObserver(Transform* playerTransform, EffectManager* effectManager, UI::ItemEffectTextManager* itemEffectTextManager);
		~ItemObserver() = default;

		void OnNotify(Event event) override {};

		void OnNotify(Event event, int value) override;

	private:

		Transform* mPlayerTransform;

		EffectManager* mEffectManager;

		UI::ItemEffectTextManager* mItemEffectTextManager;
	};
}
