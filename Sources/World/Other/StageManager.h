#pragma once

#include "../GameObject.h"
#include <string>

/// <summary>
/// ステージを生成し、管理するクラス
/// </summary>
class StageManager : public GameObject
{
public:

	StageManager(const std::string& objectDataPath);
	StageManager();

	void Init() override;
	void Update() override;
};
