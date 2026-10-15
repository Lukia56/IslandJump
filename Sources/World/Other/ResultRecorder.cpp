#include "ResultRecorder.h"
#include <cmath>
#include "System/TimeManager.h"

namespace
{
	constexpr float kOneMinuteSec = 60.0f;
}

ResultRecorder::ResultRecorder(Transform* playerTransform) :
	mProgressDistance(0),
	mIsSuccessed(false),
	mItemUseCount(0),
	mPlayTime(0.0f),
	mIsCountPlayTime(true),
	mPlayerTransform(nullptr)
{
}

ResultRecorder::ResultRecorder() :
	mProgressDistance(0),
	mIsSuccessed(false),
	mItemUseCount(0),
	mPlayTime(0.0f),
	mIsCountPlayTime(true),
	mPlayerTransform(nullptr)
{
}

void ResultRecorder::Init()
{
}

void ResultRecorder::Update()
{
	if (mIsCountPlayTime)
	{
		mPlayTime += TimeManager::GetDeltaTime();
	}

	if (!mPlayerTransform) return;

	int playerY = static_cast<int>(mPlayerTransform->CalculateWorldPosition().y);
	mProgressDistance = Math::Max(mProgressDistance, playerY);
}

ResultData ResultRecorder::CreateResultData() const
{
	ResultData result{};

	result.isSuccessed = mIsSuccessed;

	result.progressDistance = mProgressDistance;

	result.itemUseCount = mItemUseCount;

	result.playMinutes = static_cast<int>(std::floor(mPlayTime / kOneMinuteSec));
	result.playSeconds = static_cast<int>(std::floor(mPlayTime - result.playMinutes * kOneMinuteSec));
	
	return result;
}
