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

	const float kHypotenuseMaxDistCoef = std::sqrt(2.0f) / 2.0f;

	// 分岐して生成する数
	constexpr int kBranchGenerateNum = 2;
	// 集合地点含めた生成数
	constexpr int kBranchGenerateNumContainAssemble = 3;

	constexpr float kBranchChance = 30.0f;
}

namespace Stage
{
	StageGenerator::GameObjectContainer StageGenerator::Generate(Vector3& goalPos)
	{
		GameObjectContainer islands;

		Mode mode = Mode::Single;

		// 開始島を生成
		{
			std::unique_ptr<RootObject> startIsland = std::make_unique<RootObject>();
			GameObjectContainer objects = Stage::StageLoader::Load(kStartIslandPath);
			for (auto& object : objects)
			{
				startIsland->AddToChild(std::move(object));
			}
			islands.emplace_back(std::move(startIsland));
		}

		// ランダムに島を生成
		Vector3 generatePos;
		float dir = 0.0f;

		int branchCount = 0;

		while (true)
		{
			if (mode == Mode::Single)
			{
				mode = GenerateIslandSingleMode(islands, generatePos, dir, goalPos.y);
			}
			else if (mode == Mode::Branch)
			{
				mode = GenerateIslandBranchMode(islands, generatePos, dir, branchCount);
			}

			if (mode == Mode::EndLoop) break;
		}

		// ゴールの座標を設定する
		generatePos.y = goalPos.y;
		goalPos = generatePos;

		return islands;
	}

	StageGenerator::Mode StageGenerator::GenerateIslandSingleMode(GameObjectContainer& islandContainer, Vector3& generatePos, float& dir, float goalPosY)
	{
		constexpr float generateRangeRad = Math::ToRadian(kGenerateRangeAngle);

		// 次の生成場所を計算する
		dir += Random::Range(-generateRangeRad * 0.5f, generateRangeRad * 0.5f);
		float distance = Random::Range(kGenerateRangeHMinDistance, kGenerateRangeHMaxDistance);
		generatePos += Vector3(
			std::sin(dir) * distance,
			Random::Range(kGenerateRangeVMinDistance, kGenerateRangeVMaxDistance),
			std::cos(dir) * distance
		);

		// ゴール場所を超えたら生成終了
		if (generatePos.y > goalPosY) return Mode::EndLoop;

		// 島を生成
		std::unique_ptr<GameObject> island = std::move(GenerateIsland());
		island->GetTransform()->localPosition = generatePos;

		islandContainer.emplace_back(std::move(island));

		// 分岐させたらゴールを超えるかチェック
		float branchModeMaxHeight = kGenerateRangeVMaxDistance * kBranchGenerateNumContainAssemble;
		if (generatePos.y + branchModeMaxHeight > goalPosY) return Mode::Single;

		// 生成するか抽選
		if (!Random::Judge(kBranchChance)) return Mode::Single;

		return Mode::Branch;
	}

	StageGenerator::Mode StageGenerator::GenerateIslandBranchMode(GameObjectContainer& islandContainer, Vector3& generatePos, float dir, int& branchCount)
	{
		// 座標を設定
		float generatePosY = Random::Range(kGenerateRangeVMinDistance, kGenerateRangeVMaxDistance);

		// 最大距離をそのまま使うと合流時にプレイヤーが届かなくなるため、斜辺が最大距離になるように計算
		float maxHDistance = kGenerateRangeHMaxDistance * kHypotenuseMaxDistCoef;
		float distance = Random::Range(kGenerateRangeHMinDistance, maxHDistance);

		float rotate = Math::kPiOver2;

		Vector3 branchPos[] = {
			generatePos + Vector3(
				std::sin(dir + rotate) * distance,
				generatePosY,
				std::cos(dir + rotate) * distance
			),
			generatePos + Vector3(
				std::sin(dir - rotate) * distance,
				generatePosY,
				std::cos(dir - rotate) * distance
			)
		};

		// 島を生成
		for (int i = 0; i < kBranchGenerateNum; i++)
		{
			std::unique_ptr<GameObject> island = std::move(GenerateIsland());
			island->GetTransform()->localPosition = branchPos[i];

			islandContainer.emplace_back(std::move(island));
		}

		generatePos += Vector3(
			std::sin(dir) * distance,
			generatePosY,
			std::cos(dir) * distance
		);

		branchCount++;

		// 分岐が終了するならMode::Singleに戻す
		if (branchCount < kBranchGenerateNum) return Mode::Branch;
		
		generatePos.y += Random::Range(kGenerateRangeVMinDistance, kGenerateRangeVMaxDistance);

		std::unique_ptr<GameObject> island = std::move(GenerateIsland());
		island->GetTransform()->localPosition = generatePos;

		islandContainer.emplace_back(std::move(island));

		branchCount = 0;

		return Mode::Single;
	}

	std::unique_ptr<GameObject> StageGenerator::GenerateIsland()
	{
		std::unique_ptr<RootObject> island = std::make_unique<RootObject>();

		int islandIndex = Random::Range(0, static_cast<int>(kIslandTypeNum));

		// 島を形成するオブジェクトを生成
		std::vector<std::unique_ptr<GameObject>> objects = Stage::StageLoader::Load(kIslandPaths[islandIndex]);
		for (auto& object : objects)
		{
			island->AddToChild(std::move(object));
		}

		return island;
	}
}
