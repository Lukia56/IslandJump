#include "ItemSpawnerManager.h"
#include <memory>
#include <vector>
#include "ItemObjectManager.h"
#include "RootObject.h"
#include "../Object/ItemSpawner.h"
#include "Utility/Random.h"

ItemSpawnerManager::ItemSpawnerManager(GameObject* stageManager, LandTerrainRecorder* landTerrainRecorder, ItemObjectManager* itemObjectManager, int itemNum) :
	mSpawnerRoot(nullptr)
{
	mSpawnerRoot = CreateToChild<RootObject>();

	std::vector<std::unique_ptr<GameObject>>& objects = stageManager->GetTransform()->GetChildren();

	std::vector<size_t> indices;
	for (int i = 0; i < objects.size() - 1; i++)
	{
		indices.emplace_back(i);
	}

	for (int i = 0; i < itemNum; i++)
	{
		if (indices.empty()) break;

		size_t index = Random::Range(static_cast<size_t>(0), indices.size());
		mSpawnerRoot->CreateToChild<ItemSpawner>(objects[indices[index]]->GetTransform(), landTerrainRecorder, itemObjectManager);

		indices.erase(indices.begin() + index);
	}
}

void ItemSpawnerManager::Init()
{
}

void ItemSpawnerManager::Update()
{
}
