#include "ItemSpawnerManager.h"
#include <memory>
#include <vector>
#include "ItemObjectManager.h"
#include "ItemSpawner.h"
#include "Utility/Random.h"
#include "World/Other/RootObject.h"

ItemSpawnerManager::ItemSpawnerManager(GameObject* stageManager, PlayerLandRecorder* landTerrainRecorder, ItemObjectManager* itemObjectManager, int itemNum) :
	mSpawnerRoot(nullptr)
{
	mSpawnerRoot = CreateToChild<RootObject>();

	std::vector<std::unique_ptr<GameObject>>& objects = stageManager->GetTransform()->GetChildren();

	std::vector<size_t> indices;
	for (int i = 1; i < objects.size() - 2; i++)
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
