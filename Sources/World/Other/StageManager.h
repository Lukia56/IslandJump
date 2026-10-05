#pragma once

#include "../GameObject.h"
#include <string>

class GoalObject;

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

public:

	GoalObject* GetGoalObject() const { return mGoalObject; }

private:

	GoalObject* mGoalObject;
};
