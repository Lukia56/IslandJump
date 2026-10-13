#pragma once

#include <memory>

namespace Resource
{
	class ResourceBase;
}

/// <summary>
/// Œø‰Ê‰¹ABGM‚ÌÄ¶‚ğs‚¤
/// </summary>
class SoundManager
{
private:

	SoundManager();
	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;
	SoundManager(SoundManager&&) = delete;
	SoundManager& operator=(SoundManager&&) = delete;

public:

	~SoundManager() = default;

	void Update();

	void PlaySe(std::shared_ptr<Resource::ResourceBase> sound);

	void PlayBGM(std::shared_ptr<Resource::ResourceBase> bgm);

	void StopBGM();

	static SoundManager& GetInstance();

private:

	void CrossFading();

private:

	std::shared_ptr<Resource::ResourceBase> m_currentBgmHandle;

	std::shared_ptr<Resource::ResourceBase> m_nextBgmHandle;

	float m_currentBgmVolume;

	float m_nextBgmVolume;

	float m_bgmFadeSpeed;

	bool m_doCrossFading;
};
