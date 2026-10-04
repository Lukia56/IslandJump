#include "StageGenerator.h"
#include <memory>
#include <string>
#include <vector>
#include "Stage/StageLoader.h"
#include "World/GameObject.h"
#include "World/Other/RootObject.h"

namespace
{
	const char* const kStartIslandPath = "Resources\\MasterData\\Island\\StartIsland.json";
}

namespace Stage
{
	std::vector<std::unique_ptr<GameObject>> StageGenerator::Generate()
	{
		std::vector<std::unique_ptr<GameObject>> islands;

		std::vector<std::unique_ptr<GameObject>> objects;

		// ŠJn“‡‚ğ¶¬
		std::unique_ptr<RootObject> startIsland = std::make_unique<RootObject>();
		objects = Stage::StageLoader::Load(kStartIslandPath);
		for (auto& object : objects)
		{
			startIsland->AddToChild(std::move(object));
		}
		islands.emplace_back(std::move(startIsland));

		return islands;
	}
}
