#include "EffectInstance.h"
#include <EffekseerForDXLib.h>
#include "System/Resource/ResourceBase.h"

EffectInstance::EffectInstance() :
	mEffectPlayHandle(-1),
	mResource(nullptr)
{
}

EffectInstance::~EffectInstance()
{
	if (mEffectPlayHandle != -1) StopEffekseer3DEffect(mEffectPlayHandle);
}

void EffectInstance::Init()
{
}

void EffectInstance::Update()
{
	if (!mResource) return;
	if (!IsPlaying()) return;

	// Ä¶‚ªI—¹‚µ‚Ä‚¢‚½‚ç
	if (IsEffekseer3DEffectPlaying(mEffectPlayHandle) == -1)
	{
		mEffectPlayHandle = -1;
		return;
	}

	Vector3 worldPos = mTransform->CalculateWorldPosition();
	SetPosPlayingEffekseer3DEffect(mEffectPlayHandle, worldPos.x, worldPos.y, worldPos.z);
}

void EffectInstance::Play(std::shared_ptr<Resource::ResourceBase> effect)
{
	if (IsPlaying()) return;

	mResource = effect;

	mEffectPlayHandle = PlayEffekseer3DEffect(mResource->GetHandle());
}

void EffectInstance::Stop()
{
	if (!IsPlaying()) return;

	StopEffekseer3DEffect(mEffectPlayHandle);

	mEffectPlayHandle = -1;
}
