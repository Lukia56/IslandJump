#include "ResultRecorder.h"
#include <cmath>
#include "Param/Param.h"
#include "System/TimeManager.h"

namespace
{
	constexpr float kOneMinuteSec = 60.0f;

	constexpr float kDistanceScoreCoef = 0.5f;
	constexpr float kItemScoreCoef = 1000.0f;
	constexpr float kTimeScoreCoef = 3.5f;
}

ResultRecorder::ResultRecorder(Transform* playerTransform) :
	mProgressDistance(0),
	mIsSuccessed(false),
	mItemUseCount(0),
	mPlayTime(0.0f),
	mIsCountPlayTime(true),
	mPlayerTransform(nullptr),
	mDifficultyData(nullptr)
{
}

ResultRecorder::ResultRecorder(StageDifficultyData* difficultyData) :
	mProgressDistance(0),
	mIsSuccessed(false),
	mItemUseCount(0),
	mPlayTime(0.0f),
	mIsCountPlayTime(true),
	mPlayerTransform(nullptr),
	mDifficultyData(difficultyData)
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
	mProgressDistance = Math::Clamp(mProgressDistance, playerY, static_cast<int>(mDifficultyData->goalPosY));
}

ResultData ResultRecorder::CreateResultData() const
{
	ResultData result{};

	result.isSuccessed = mIsSuccessed;

	result.progressDistance = mProgressDistance;

	result.itemUseCount = mItemUseCount;

	result.playMinutes = static_cast<int>(std::floor(mPlayTime / kOneMinuteSec));
	result.playSeconds = static_cast<int>(std::floor(mPlayTime - result.playMinutes * kOneMinuteSec));

	// スコアを計算
	result.distanceScore = mProgressDistance * kDistanceScoreCoef;
	result.itemScore = mItemUseCount * kItemScoreCoef;

	float progress = mDifficultyData->goalPosY / mDifficultyData->cloudSpeed;
	result.timeScore = Math::Sqr(Math::Max(0.0f, progress - mPlayTime)) * kTimeScoreCoef * mIsSuccessed;
	
	return result;
}
