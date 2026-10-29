#include "ItemUseCountUI.h"
#include <string>
#include "../ImageObject.h"
#include "../TextObject.h"
#include "System/Resource/ResourceBase.h"
#include "World/Object/Item/ItemObjectManager.h"

namespace
{
	constexpr Vector3 kCountTextPos{ 50.0f, 0.0f, 0.0f };
}

UI::ItemUseCountUI::ItemUseCountUI(ItemType itemType, ItemObjectManager* itemObjectManager, std::shared_ptr<Resource::ResourceBase> font) :
	mItemType(itemType),
	mItemObjectManager(itemObjectManager),
	mCountText(nullptr)
{
	mCountText = CreateToChild<UI::TextObject>(font, "", Color::white, HolizontalAlignment::Left, VerticalAlignment::Middle);
	mCountText->GetRectTransform()->localPosition = kCountTextPos;
}

void UI::ItemUseCountUI::Init()
{
	UI::ImageObject* icon = CreateToChild<UI::ImageObject>(mItemObjectManager->GetTextures()[static_cast<size_t>(mItemType)]);
}

void UI::ItemUseCountUI::Update()
{
	int count = mItemObjectManager->GetItemUseCounts()[static_cast<size_t>(mItemType)];
	mCountText->SetDisplayText(std::to_string(count));
}
