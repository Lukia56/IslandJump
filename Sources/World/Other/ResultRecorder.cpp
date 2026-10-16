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

	constexpr float kHardModeScoreCoef = 2.0f;
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
	result.playTenMilliSeconds = static_cast<int>(std::floor((mPlayTime - result.playSeconds - result.playMinutes * kOneMinuteSec) * 100.0f));

	// スコアを計算
	result.distanceScore = static_cast<int>(mProgressDistance * kDistanceScoreCoef);
	result.itemScore = static_cast<int>(mItemUseCount * kItemScoreCoef);

	float progress = mDifficultyData->goalPosY / mDifficultyData->cloudSpeed;
	result.timeScore = static_cast<int>(Math::Sqr(Math::Max(0.0f, progress - mPlayTime)) * kTimeScoreCoef * mIsSuccessed);

	float scoreCoef = mDifficultyData->difficulty == StageDifficultyData::Difficulty::Hard ? kHardModeScoreCoef : 1.0f;
	result.overallScore = static_cast<int>((result.distanceScore + result.itemScore + result.timeScore) * scoreCoef);
	
	return result;
}
