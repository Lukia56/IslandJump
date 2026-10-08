#pragma once

#include "../GameObject.h"
#include "ResultData.h"

class ItemObjectManager;

class ResultRecorder : public GameObject
{
public:

	ResultRecorder(Transform* playerTransform);
	~ResultRecorder() = default;

	void Init() override;

	void Update() override;

	ResultData CreateResultData() const;

	void IncreaseItemUseCount() { mItemUseCount++; }

public:

	void SetSuccessed(bool flag) { mIsSuccessed = flag; }

private:

	bool mIsSuccessed;

	int mItemUseCount;

	float mPlayTime;

	Transform* mPlayerTransform;
};
