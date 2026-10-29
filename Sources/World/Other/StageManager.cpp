#include "StageManager.h"
#include <memory>
#include <string>
#include <vector>
#include "Stage/StageGenerator.h"
#include "Stage/StageLoader.h"
#include "World/Object/Goal/GoalObject.h"

namespace
{
	constexpr Vector3 kGoalOffset{ 0.0f, 100.0f, 0.0f };
}

StageManager::StageManager(std::shared_ptr<Resource::ResourceBase> goalModel, float goalY) :
	mGoalObject(nullptr)
{
	Vector3 goalPos = Vector3(0.0f, goalY, 0.0f);

	std::vector<std::unique_ptr<GameObject>> objects = Stage::StageGenerator::Generate(goalPos);

	for (auto& object : objects)
	{
		AddToChild(std::move(object));
	}

	mGoalObject = CreateToChild<GoalObject>(goalModel);
	mGoalObject->GetTransform()->localPosition = goalPos + kGoalOffset;
}

void StageManager::Init()
{
}

void StageManager::Update()
{
}
