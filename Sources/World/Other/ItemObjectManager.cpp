#include "ItemObjectManager.h"
#include <algorithm>
#include "../Object/ItemObject.h"
#include "../Object/ItemTextureDataBase.h"
#include "RootObject.h"
#include "System/ResourceManager.h"
#include "System/Resource/Texture.h"
#include "Utility/Random.h"
#include "Utility/Data/CSV/CsvLoader.h"

namespace
{
	const char* const kEffectParamPath = "Resources\\MasterData\\ItemEffectParam.csv";
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

	ItemTextureDataBase textureDataBase;

	for (int i = 0; i < static_cast<int>(ItemType::Length); i++)
	{
		std::string filePath = textureDataBase.GetFilePath(static_cast<ItemType>(i));
		std::shared_ptr<Resource::ResourceBase> texture = ResourceManager::GetInstance().GetResource<Resource::Texture>(filePath);
		mTextures[i] = texture;
	}

	mEffectParams = Data::Csv::LoadCsvAs<ItemEffectParam>(kEffectParamPath);
}

void ItemObjectManager::Update()
{
}

void ItemObjectManager::CreateItem(const Vector3& pos)
{
	// ランダムなアイテムの種類を取得
	ItemType itemType = static_cast<ItemType>(Random::Range(0, static_cast<int>(ItemType::Length)));

	// プールから取り出す
	ItemObject* item = mPoolItems.top();

	item->GetTransform()->ChangeParent(mActiveItemRoot->GetTransform());
	item->Setup(pos, mTextures[static_cast<int>(itemType)], itemType);

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

	mItemUseCount++;

	return itemType;
}
