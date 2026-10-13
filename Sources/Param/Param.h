#pragma once

#include <string>
#include <vector>
#include "TempParam.h"
#include "Collision/CollisionTag.h"
#include "Utility/Vector.h"
#include "World/Object/ItemType.h"

struct WindowConfigs
{
	std::string windowText = "";
	int width = 0;
	int height = 0;
	int colorBit = 0;
};

struct AABBColliderParam
{
	Vector3 size{};
	Vector3 offsetPos{};
	Collision::Tag collisionTag = Collision::Tag::Invalid;
};

struct AnimationParam
{
	int animIndex = 0;
	bool isLoop = false;
	bool isForcePlay = false;
};

struct StageObjectParam
{
	std::string name = "";
	TempTransform transform{};
	TempBounds bounds{};
};

struct StageModelData
{
	std::string objectName = "";
	std::string filePath = "";
};

struct ItemTextureData
{
	ItemType itemType = ItemType::Invalid;
	std::string filePath = "";
};

struct ItemEffectParam
{
	ItemType itemType = ItemType::Invalid;
	std::vector<float> param;
};

struct StageDifficultyData
{
	enum class Difficulty
	{
		Easy,
		Hard,
	};

	float cloudSpeed = 0.0f;

	int itemNum = 0;
};

struct SoundData
{
	int id = -1;
	std::string filePath = "";
};
