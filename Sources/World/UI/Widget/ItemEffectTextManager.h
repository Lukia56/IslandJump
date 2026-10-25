#pragma once

#include "../Core/UIObject.h"
#include <stack>
#include "World/Object/ItemType.h"

namespace Resource
{
	class ResourceBase;
}

namespace UI
{
	class UIRoot;
	class ItemEffectText;

	class ItemEffectTextManager : public UIObject
	{
	public:

		ItemEffectTextManager(std::shared_ptr<Resource::ResourceBase> font, int maxNum);

		void Init() override;

		void Update() override;

		void Create(ItemType itemType);

	private:

		UIRoot* mActiveRoot;

		UIRoot* mPoolRoot;

		std::vector<ItemEffectText*> mActiveTexts;

		std::stack<ItemEffectText*> mPoolTexts;
	};
}
