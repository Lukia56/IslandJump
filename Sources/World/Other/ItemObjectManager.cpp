#include "ItemObjectManager.h"
#include <algorithm>
#include "../Object/ItemObject.h"
#include "RootObject.h"
#include "Utility/Random.h"

#include "System/ResourceManager.h"
#include "System/Resource/Texture.h"

namespace
{
	const char* const kTempTexPath = "Resources\\Sprite\\TempItem.png";
}

ItemObjectManager::ItemObjectManager(int itemNum) :
	mActiveItemRoot(nullptr),
	mPoolItemRoot(nullptr)
{
	mPoolItemRoot = CreateToChild<RootObject>();
	mPoolItemRoot->SetActive(false);

	for (int i = 0; i < itemNum; i++)
	{
		ItemObject* item = mPoolItemRoot->CreateToChild<ItemObject>();
		mPoolItems.emplace(item);
	}
}

void ItemObjectManager::Init()
{
	mActiveItemRoot = CreateToChild<RootObject>();
}

void ItemObjectManager::Update()
{
}

void ItemObjectManager::CreateItem(const Vector3& pos)
{
	// ランダムなアイテムの種類を取得
	ItemType itemType = static_cast<ItemType>(Random::Range(0, static_cast<int>(ItemType::Length)));

	// TODO: アイテムごとのアイコンの配列から取り出すようにする
	auto res = ResourceManager::GetInstance().GetResource<Resource::Texture>(kTempTexPath);

	// プールから取り出す
	ItemObject* item = mPoolItems.top();

	item->GetTransform()->ChangeParent(mActiveItemRoot->GetTransform());
	item->Setup(pos, res, itemType);

	mPoolItems.pop();
	mActiveItems.emplace_back(item);
}

ItemType ItemObjectManager::ConsumeItem(Transform* itemTransform)
{
	auto iter = std::find_if(mActiveItems.begin(), mActiveItems.end(), [&itemTransform](ItemObject* item)
		{
			return item->GetTransform() == itemTransform;
		});

	if (iter == mActiveItems.end()) return ItemType::Invalid;

	ItemObject* item = *iter;

	ItemType itemType = item->GetItemType();

	// プールに移動させる
	item->GetTransform()->ChangeParent(mPoolItemRoot->GetTransform());

	mActiveItems.erase(iter);
	mPoolItems.emplace(item);

	return itemType;
}
