#pragma once

#include "../GameObject.h"
#include "ResultData.h"

struct StageDifficultyData;
class ItemObjectManager;

class ResultRecorder : public GameObject
{
public:

	ResultRecorder(StageDifficultyData* difficultyData);
	~ResultRecorder() = default;

	void Init() override;

	void Update() override;

	ResultData CreateResultData() const;

	void IncreaseItemUseCount() { mItemUseCount++; }

public:

	void SetProgressDistance(int progress) { mProgressDistance = progress; }

	void SetSuccessed(bool flag) { mIsSuccessed = flag; }

	void SetPlayerTransform(Transform* transform) { mPlayerTransform = transform; }

private:

	int mProgressDistance;

	bool mIsSuccessed;

	int mItemUseCount;

	Transform* mPlayerTransform;

	StageDifficultyData* mDifficultyData;
};
