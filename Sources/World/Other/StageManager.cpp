#include "StageManager.h"
#include <memory>
#include <string>
#include <vector>
#include "Stage/StageGenerator.h"
#include "Stage/StageLoader.h"
#include "World/Object/GoalObject.h"

StageManager::StageManager(const std::string& objectDataPath) :
	mGoalObject(nullptr)
{
	std::vector<std::unique_ptr<GameObject>> objects = Stage::StageLoader::Load(objectDataPath);

	for (auto& object : objects)
	{
		AddToChild(std::move(object));
	}
}

StageManager::StageManager() :
	mGoalObject(nullptr)
{
	Vector3 goalPos;

	std::vector<std::unique_ptr<GameObject>> objects = Stage::StageGenerator::Generate(goalPos);

	for (auto& object : objects)
	{
		AddToChild(std::move(object));
	}

	mGoalObject = CreateToChild<GoalObject>();
	mGoalObject->GetTransform()->localPosition = goalPos;
}

void StageManager::Init()
{
}

void StageManager::Update()
{
}
