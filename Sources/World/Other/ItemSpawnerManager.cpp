#include "ItemSpawnerManager.h"
#include <memory>
#include <vector>
#include "RootObject.h"
#include "../Object/ItemSpawner.h"
#include "Utility/Random.h"

namespace
{
	constexpr int kSpawnerNum = 10;
}

ItemSpawnerManager::ItemSpawnerManager(GameObject* stageManager, LandTerrainRecorder* landTerrainRecorder) :
	mItemRoot(nullptr),
	mSpawnerRoot(nullptr)
{
	mItemRoot = CreateToChild<RootObject>();
	mSpawnerRoot = CreateToChild<RootObject>();

	std::vector<std::unique_ptr<GameObject>>& objects = stageManager->GetTransform()->GetChildren();

	std::vector<size_t> indices;
	for (int i = 0; i < objects.size(); i++)
	{
		indices.emplace_back(i);
	}

	for (int i = 0; i < kSpawnerNum; i++)
	{
		if (indices.empty()) break;

		size_t index = Random::Range(static_cast<size_t>(0), indices.size());
		mSpawnerRoot->CreateToChild<ItemSpawner>(objects[indices[index]]->GetTransform(), landTerrainRecorder, mItemRoot);

		indices.erase(indices.begin() + index);
	}
}

void ItemSpawnerManager::Init()
{
}

void ItemSpawnerManager::Update()
{
}
