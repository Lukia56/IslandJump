#pragma once

#include <memory>
#include <vector>
#include "Utility/Vector.h"

class GameObject;

namespace Stage
{
	class StageGenerator
	{
	public:

		using GameObjectContainer = std::vector<std::unique_ptr<GameObject>>;

		static GameObjectContainer Generate(Vector3& goalPos);

	private:

		enum class Mode
		{
			Single,
			Branch,
			EndLoop,
		};

	private:

		static Mode GenerateIslandSingleMode(GameObjectContainer& islandContainer, Vector3& generatePos, float& dir, float goalPosY);

		static Mode GenerateIslandBranchMode(GameObjectContainer& islandContainer, Vector3& generatePos, float dir, int& branchCount);

		static std::unique_ptr<GameObject> GenerateIsland();
	};
}
