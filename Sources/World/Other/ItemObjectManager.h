#pragma once

#include "../GameObject.h"
#include <array>
#include <stack>
#include <vector>
#include "../Object/ItemType.h"
#include "Param/Param.h"

class ItemObject;
class ResultRecorder;
namespace Resource
{
	class ResourceBase;
}

/// <summary>
/// 配置されるアイテムをプールで管理する
/// </summary>
class ItemObjectManager : public GameObject
{
public:

	ItemObjectManager(int itemNum, ResultRecorder* resultRecorder);
	~ItemObjectManager() = default;

	void Init() override;

	void Update() override;

	void CreateItem(const Vector3& pos);

	ItemType ConsumeItem(Transform* itemTransform);

public:

	const std::array<std::shared_ptr<Resource::ResourceBase>, static_cast<int>(ItemType::Length)>& GetTextures() const { return mTextures; }

	const ItemEffectParam& GetEffectParam(ItemType itemType) const { return mEffectParams[static_cast<int>(itemType)]; }

	const std::array<int, static_cast<size_t>(ItemType::Length)>& GetItemUseCounts() const { return mItemUseCounts; }
	void AddItemUseCount(ItemType itemType) { mItemUseCounts[static_cast<size_t>(itemType)]++; }

private:

	GameObject* mActiveItemRoot;
	GameObject* mPoolItemRoot;

	std::array<std::shared_ptr<Resource::ResourceBase>, static_cast<int>(ItemType::Length)> mTextures;

	std::vector<ItemEffectParam> mEffectParams;

	std::array<int, static_cast<size_t>(ItemType::Length)> mItemUseCounts;

	std::vector<ItemObject*> mActiveItems;
	std::stack<ItemObject*> mPoolItems;

	ResultRecorder* mResultRecorder;
};
