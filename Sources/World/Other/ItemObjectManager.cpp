#include "ItemObjectManager.h"
#include <algorithm>
#include "../Object/ItemObject.h"
#include "RootObject.h"

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
	// TODO: アイテムごとのアイコンの配列から取り出すようにする
	auto res = ResourceManager::GetInstance().GetResource<Resource::Texture>(kTempTexPath);

	// プールから取り出す
	ItemObject* item = mPoolItems.top();

	item->GetTransform()->ChangeParent(mActiveItemRoot->GetTransform());
	item->Setup(pos, res);

	mPoolItems.pop();
	mActiveItems.emplace_back(item);
}

void ItemObjectManager::ConsumeItem(Transform* itemTransform)
{
	auto iter = std::find_if(mActiveItems.begin(), mActiveItems.end(), [&itemTransform](ItemObject* item)
		{
			return item->GetTransform() == itemTransform;
		});

	if (iter == mActiveItems.end()) return;

	ItemObject* item = *iter;

	// プールに移動させる
	item->GetTransform()->ChangeParent(mPoolItemRoot->GetTransform());

	mActiveItems.erase(iter);
	mPoolItems.emplace(item);

	// TODO: アイテムの効果を返す
}
