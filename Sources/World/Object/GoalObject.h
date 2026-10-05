#pragma once

#include "../GameObject.h"

class GoalTrigger;

/// <summary>
/// ƒS[ƒ‹‚Ìƒ‚ƒfƒ‹•`‰æ‚ÆƒS[ƒ‹”»’è‚ğs‚¤
/// </summary>
class GoalObject : public GameObject
{
public:

	GoalObject();
	~GoalObject() = default;

	void Init();

	void Update();

public:

	GoalTrigger* GetTrigger() const { return mTrigger; }

private:

	GoalTrigger* mTrigger;
};
