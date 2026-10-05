#pragma once

#include "../GameObject.h"
#include <array>
#include <stack>
#include "../Object/ItemType.h"

class ItemObject;
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

	ItemObjectManager(int itemNum);
	~ItemObjectManager() = default;

	void Init() override;

	void Update() override;

	void CreateItem(const Vector3& pos);

	ItemType ConsumeItem(Transform* itemTransform);

private:

	GameObject* mActiveItemRoot;
	GameObject* mPoolItemRoot;

	std::array<std::shared_ptr<Resource::ResourceBase>, static_cast<int>(ItemType::Length)> mTextures;

	std::vector<ItemObject*> mActiveItems;
	std::stack<ItemObject*> mPoolItems;
};
