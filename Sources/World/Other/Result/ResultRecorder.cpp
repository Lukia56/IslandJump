#include "ResultRecorder.h"
#include "Param/Param.h"

namespace
{
	constexpr float kOneMinuteSec = 60.0f;

	constexpr float kDistanceScoreCoef = 1.0f;
	constexpr float kItemScoreCoef = 1500.0f;

	constexpr float kHardModeScoreCoef = 2.0f;
}

ResultRecorder::ResultRecorder(StageDifficultyData* difficultyData) :
	mProgressDistance(0),
	mIsSuccessed(false),
	mItemUseCount(0),
	mPlayerTransform(nullptr),
	mDifficultyData(difficultyData)
{
}

void ResultRecorder::Init()
{
}

void ResultRecorder::Update()
{
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

	// スコアを計算
	result.distanceScore = static_cast<int>(mProgressDistance * kDistanceScoreCoef);
	result.itemScore = static_cast<int>(mItemUseCount * kItemScoreCoef);

	float scoreCoef = mDifficultyData->difficulty == StageDifficultyData::Difficulty::Hard && mIsSuccessed ? kHardModeScoreCoef : 1.0f;
	result.overallScore = static_cast<int>((result.distanceScore + result.itemScore) * scoreCoef);
	
	return result;
}
