#pragma once

#include "../GameObject.h"
#include "ResultData.h"

class ItemObjectManager;

class ResultRecorder : public GameObject
{
public:

	ResultRecorder(Transform* playerTransform);
	ResultRecorder();
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

	float mPlayTime;

	Transform* mPlayerTransform;
};
