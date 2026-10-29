#pragma once

#include <string>
#include <vector>
#include "TempParam.h"
#include "Collision/CollisionTag.h"
#include "Utility/Vector.h"
#include "World/Object/Item/ItemType.h"

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

	Difficulty difficulty = Difficulty::Easy;

	float cloudSpeed = 0.0f;

	int itemNum = 0;

	float goalPosY = 0.0f;
};

struct SoundData
{
	int id = -1;
	std::string filePath = "";
};

struct SaveData
{
	int easyHighscore = 0;
	int hardHighscore = 0;
};

struct OptionsData
{
	int mouseSensitivityX = 100;
	int mouseSensitivityY = 100;
};
