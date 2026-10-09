#include "StageGenerator.h"
#include <array>
#include <memory>
#include <string>
#include <vector>
#include "Stage/StageLoader.h"
#include "Utility/Math.h"
#include "Utility/Random.h"
#include "World/GameObject.h"
#include "World/Other/RootObject.h"

namespace
{
	const char* const kStartIslandPath = "Resources\\MasterData\\Island\\StartIsland.json";

	const std::string kIslandPaths[] = {
		"Resources\\MasterData\\Island\\Island0.json",
		"Resources\\MasterData\\Island\\Island1.json",
		"Resources\\MasterData\\Island\\Island2.json",
	};
	constexpr size_t kIslandTypeNum = 3;

	constexpr float kGenerateRangeAngle = 90.0f;

	constexpr float kGenerateRangeHMinDistance = 400.0f;
	constexpr float kGenerateRangeHMaxDistance = 800.0f;
	constexpr float kGenerateRangeVMinDistance = 200.0f;
	constexpr float kGenerateRangeVMaxDistance = 400.0f;

	constexpr float kGoalPosY = 5000.0f;
}

namespace Stage
{
	std::vector<std::unique_ptr<GameObject>> StageGenerator::Generate(Vector3& goalPos)
	{
		std::vector<std::unique_ptr<GameObject>> islands;

		std::vector<std::unique_ptr<GameObject>> objects;

		// 開始島を生成
		std::unique_ptr<RootObject> startIsland = std::make_unique<RootObject>();
		objects = Stage::StageLoader::Load(kStartIslandPath);
		for (auto& object : objects)
		{
			startIsland->AddToChild(std::move(object));
		}
		islands.emplace_back(std::move(startIsland));

		// ランダムに島を生成
		Vector3 generatePos;
		float dir = 0.0f;
		constexpr float generateRangeRad = Math::ToRadian(kGenerateRangeAngle);

		while (generatePos.y < kGoalPosY)
		{
			std::unique_ptr<RootObject> island = std::make_unique<RootObject>();
			int islandIndex = Random::Range(0, static_cast<int>(kIslandTypeNum));
			objects = Stage::StageLoader::Load(kIslandPaths[islandIndex]);
			for (auto& object : objects)
			{
				island->AddToChild(std::move(object));
			}

			dir = Random::Range(-generateRangeRad * 0.5f, generateRangeRad * 0.5f);
			float distance = Random::Range(kGenerateRangeHMinDistance, kGenerateRangeHMaxDistance);
			generatePos += Vector3(
				std::sin(dir) * distance,
				Random::Range(kGenerateRangeVMinDistance, kGenerateRangeVMaxDistance),
				std::cos(dir) * distance
			);

			island->GetTransform()->localPosition = generatePos;

			islands.emplace_back(std::move(island));
		}

		// ゴールの座標を計算する
		float distance = Random::Range(kGenerateRangeHMinDistance, kGenerateRangeHMaxDistance);
		generatePos += Vector3(
			std::sin(dir) * distance,
			Random::Range(kGenerateRangeVMinDistance, kGenerateRangeVMaxDistance),
			std::cos(dir) * distance
		);
		goalPos = generatePos;

		return islands;
	}
}
