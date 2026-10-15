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

	constexpr float kGenerateRangeAngle = 180.0f;

	constexpr float kGenerateRangeHMinDistance = 500.0f;
	constexpr float kGenerateRangeHMaxDistance = 900.0f;
	constexpr float kGenerateRangeVMinDistance = 300.0f;
	constexpr float kGenerateRangeVMaxDistance = 500.0f;
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

		while (true)
		{
			std::unique_ptr<RootObject> island = std::make_unique<RootObject>();
			int islandIndex = Random::Range(0, static_cast<int>(kIslandTypeNum));
			objects = Stage::StageLoader::Load(kIslandPaths[islandIndex]);
			for (auto& object : objects)
			{
				island->AddToChild(std::move(object));
			}

			dir += Random::Range(-generateRangeRad * 0.5f, generateRangeRad * 0.5f);
			float distance = Random::Range(kGenerateRangeHMinDistance, kGenerateRangeHMaxDistance);
			generatePos += Vector3(
				std::sin(dir) * distance,
				Random::Range(kGenerateRangeVMinDistance, kGenerateRangeVMaxDistance),
				std::cos(dir) * distance
			);

			if (generatePos.y > goalPos.y) break;

			island->GetTransform()->localPosition = generatePos;

			islands.emplace_back(std::move(island));

			// 次に生成する島の種類を決める

				// 通常：ランダムに決める
				// 分岐：2つ生成する、次の島は通常にする
					// 次に生成する座標は片方にする
		}

		// ゴールの座標を設定する
		generatePos.y = goalPos.y;
		goalPos = generatePos;

		return islands;
	}
}
