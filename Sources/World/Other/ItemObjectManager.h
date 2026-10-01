#pragma once

#include "../GameObject.h"
#include <stack>

class ItemObject;

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

	void ConsumeItem(Transform* itemTransform);

private:

	GameObject* mActiveItemRoot;
	GameObject* mPoolItemRoot;

	std::vector<ItemObject*> mActiveItems;
	std::stack<ItemObject*> mPoolItems;
};
