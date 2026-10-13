#pragma once

#include "../Core/UIObject.h"
#include "World/Object/ItemType.h"

class ItemObjectManager;
namespace Resource
{
	class ResourceBase;
}

namespace UI
{
	class TextObject;

	class ItemUseCountUI : public UIObject
	{
	public:

		ItemUseCountUI(ItemType itemType, ItemObjectManager* itemObjectManager, std::shared_ptr<Resource::ResourceBase> font);
		~ItemUseCountUI() = default;

		void Init() override;

		void Update() override;

	private:

		ItemType mItemType;

		ItemObjectManager* mItemObjectManager;

		TextObject* mCountText;
	};
}
