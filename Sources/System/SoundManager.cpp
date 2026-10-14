#include "SoundManager.h"
#include <cassert>
#include <DxLib.h>
#include "System/Resource/ResourceBase.h"
#include "System/TimeManager.h"
#include "Utility/Math.h"

namespace
{
	constexpr float kDefaultFadeSpeed = 255.0f;

	constexpr float kMaxVolume = 255.0f;
	constexpr float kMinVolume = 0.0f;
}

SoundManager::SoundManager() :
	mCurrentBgmResource(nullptr),
	mNextBgmResource(nullptr),
	mCurrentBgmVolume(kMaxVolume),
	mNextBgmVolume(kMinVolume),
	mBgmFadeSpeed(kDefaultFadeSpeed),
	mDoCrossFading(false)
{
}

void SoundManager::Update()
{
	CrossFading();

	if (mCurrentBgmResource) ChangeVolumeSoundMem(mCurrentBgmVolume, mCurrentBgmResource->GetHandle());

	if (mNextBgmResource) ChangeVolumeSoundMem(mNextBgmVolume, mNextBgmResource->GetHandle());
}

void SoundManager::PlaySe(std::shared_ptr<Resource::ResourceBase> sound)
{
	if (!sound)
	{
		assert(false && "SoundManager // リソースがnullptrです");
		return;
	}

	int handle = sound->GetHandle();
	if (handle == -1)
	{
		assert(false && "SoundManager // 読み込みに失敗したSEを再生しようとしました");
		return;
	}

	PlaySoundMem(handle, DX_PLAYTYPE_BACK);

	ChangeVolumeSoundMem(static_cast<int>(kMaxVolume), handle);
}

void SoundManager::PlayBGM(std::shared_ptr<Resource::ResourceBase> bgm)
{
	if (!bgm)
	{
		assert(false && "SoundManager // リソースがnullptrです");
		return;
	}

	int handle = bgm->GetHandle();

	// 現在再生中のBGMと同じBGMを再生しようとしたら処理を行わない
	if (mCurrentBgmResource && !mNextBgmResource && mCurrentBgmResource->GetHandle() == handle) return;

	if (handle == -1)
	{
		assert(false && "SoundManager // 読み込みに失敗したBGMを再生しようとしました");
		return;
	}

	if (!mCurrentBgmResource)
	{
		mCurrentBgmResource = bgm;

		PlaySoundMem(mCurrentBgmResource->GetHandle(), DX_PLAYTYPE_LOOP);
	}
	else
	{
		if (mDoCrossFading)
		{
			StopBGM();

			mCurrentBgmResource = mNextBgmResource;
		}

		mNextBgmResource = bgm;

		mCurrentBgmVolume = kMaxVolume;
		mNextBgmVolume = kMinVolume;

		mDoCrossFading = true;

		PlaySoundMem(mNextBgmResource->GetHandle(), DX_PLAYTYPE_LOOP);
	}
}

void SoundManager::StopBGM()
{
	if (!mCurrentBgmResource) return;

	StopSoundMem(mCurrentBgmResource->GetHandle());
	mCurrentBgmResource = nullptr;
}

SoundManager& SoundManager::GetInstance()
{
	static SoundManager instance;

	return instance;
}

void SoundManager::CrossFading()
{
	if (!mDoCrossFading) return;

	float fadeSpeed = mBgmFadeSpeed * TimeManager::GetDeltaTime();

	mCurrentBgmVolume = Math::Approach(mCurrentBgmVolume, kMinVolume, fadeSpeed);
	mNextBgmVolume = Math::Approach(mNextBgmVolume, kMaxVolume, fadeSpeed);

	if (static_cast<int>(mNextBgmVolume) >= kMaxVolume)
	{
		StopBGM();

		mCurrentBgmResource = mNextBgmResource;
		mNextBgmResource = nullptr;

		mCurrentBgmVolume = kMaxVolume;

		mDoCrossFading = false;
	}
}
