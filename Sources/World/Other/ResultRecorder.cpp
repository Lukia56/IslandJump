#include "ResultRecorder.h"
#include <cmath>
#include "System/TimeManager.h"

namespace
{
	constexpr float kOneMinuteSec = 60.0f;
}

ResultRecorder::ResultRecorder(Transform* playerTransform) :
	mItemUseCount(0),
	mPlayTime(0.0f),
	mPlayerTransform(playerTransform)
{
}

void ResultRecorder::Init()
{
}

void ResultRecorder::Update()
{
	mPlayTime += TimeManager::GetDeltaTime();
}

ResultData ResultRecorder::CreateResultData() const
{
	ResultData result{};

	result.isSuccessed = mIsSuccessed;

	result.progressDistance = Math::Max(0.0f, mPlayerTransform->localPosition.y);

	result.itemUseCount = mItemUseCount;

	result.playMinutes = static_cast<int>(std::floor(mPlayTime / kOneMinuteSec));
	result.playSeconds = static_cast<int>(std::floor(mPlayTime - result.playMinutes * kOneMinuteSec));
	
	return result;
}
