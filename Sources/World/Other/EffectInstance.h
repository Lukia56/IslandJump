#pragma once

#include "../GameObject.h"

namespace Resource
{
	class ResourceBase;
}

class EffectInstance : public GameObject
{
public:

	EffectInstance();
	~EffectInstance();

	void Init() override;

	void Update() override;

	void Play(std::shared_ptr<Resource::ResourceBase> effect);

	void Stop();

	bool IsPlaying() const { return mEffectPlayHandle != -1; }

private:

	int mEffectPlayHandle;

	std::shared_ptr<Resource::ResourceBase> mResource;
};
