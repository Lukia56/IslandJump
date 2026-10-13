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
	m_currentBgmHandle(nullptr),
	m_nextBgmHandle(nullptr),
	m_currentBgmVolume(kMaxVolume),
	m_nextBgmVolume(kMinVolume),
	m_bgmFadeSpeed(kDefaultFadeSpeed),
	m_doCrossFading(false)
{
}

void SoundManager::Update()
{
	CrossFading();

	if (m_currentBgmHandle) ChangeVolumeSoundMem(m_currentBgmVolume, m_currentBgmHandle->GetHandle());

	if (m_nextBgmHandle) ChangeVolumeSoundMem(m_nextBgmVolume, m_nextBgmHandle->GetHandle());
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
	if (m_currentBgmHandle && m_currentBgmHandle->GetHandle() == handle) return;

	if (handle == -1)
	{
		assert(false && "SoundManager // 読み込みに失敗したBGMを再生しようとしました");
		return;
	}

	if (!m_currentBgmHandle)
	{
		m_currentBgmHandle = bgm;

		PlaySoundMem(m_currentBgmHandle->GetHandle(), DX_PLAYTYPE_LOOP);
	}
	else
	{
		m_nextBgmHandle = bgm;

		m_currentBgmVolume = kMaxVolume;
		m_nextBgmVolume = kMinVolume;

		m_doCrossFading = true;

		PlaySoundMem(m_nextBgmHandle->GetHandle(), DX_PLAYTYPE_LOOP);
	}
}

void SoundManager::StopBGM()
{
	if (!m_currentBgmHandle) return;

	StopSoundMem(m_currentBgmHandle->GetHandle());
	m_currentBgmHandle = nullptr;
}

SoundManager& SoundManager::GetInstance()
{
	static SoundManager instance;

	return instance;
}

void SoundManager::CrossFading()
{
	if (!m_doCrossFading) return;

	float fadeSpeed = m_bgmFadeSpeed * TimeManager::GetDeltaTime();

	m_currentBgmVolume = Math::Approach(m_currentBgmVolume, kMinVolume, fadeSpeed);
	m_nextBgmVolume = Math::Approach(m_nextBgmVolume, kMaxVolume, fadeSpeed);

	if (static_cast<int>(m_nextBgmVolume) >= kMaxVolume)
	{
		StopBGM();

		m_currentBgmHandle = m_nextBgmHandle;
		m_nextBgmHandle = nullptr;

		m_currentBgmVolume = kMaxVolume;

		m_doCrossFading = false;
	}
}
