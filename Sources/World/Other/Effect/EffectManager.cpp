#include "EffectManager.h"
#include <cassert>
#include "EffectInstance.h"
#include "../RootObject.h"
#include "System/Resource/ResourceBase.h"

EffectManager::EffectManager(int maxEffect) :
	mMaxEffect(maxEffect),
	mActiveEffectRoot(nullptr),
	mPoolEffectRoot(nullptr)
{
	mPoolEffectRoot = CreateToChild<RootObject>();
	mPoolEffectRoot->SetActive(false);

	for (int i = 0; i < maxEffect; i++)
	{
		EffectInstance* effect = CreateToChild<EffectInstance>();
		mPoolEffects.emplace(effect);
	}
}

void EffectManager::Init()
{
	mActiveEffectRoot = CreateToChild<RootObject>();
}

void EffectManager::Update()
{
	// 再生が終了したインスタンスを削除する
	for (auto iter = mActiveEffects.begin(); iter != mActiveEffects.end();)
	{
		EffectInstance* effect = *iter;

		if (effect->IsPlaying())
		{
			iter++;
			continue;
		}

		effect->GetTransform()->ChangeParent(mPoolEffectRoot->GetTransform());

		mPoolEffects.emplace(effect);
		iter = mActiveEffects.erase(iter);
	}
}

EffectInstance* EffectManager::Play(std::string filePath, const Vector3& pos)
{
	assert(mResources.contains(filePath) && "EffectManager // まだ登録されていないエフェクトを再生しようとしています");
	std::shared_ptr<Resource::ResourceBase> resource = mResources.at(filePath);

	// プールから取り出す
	EffectInstance* effect = mPoolEffects.top();

	effect->GetTransform()->localPosition = pos;
	effect->GetTransform()->ChangeParent(mActiveEffectRoot->GetTransform());

	mPoolEffects.pop();
	mActiveEffects.emplace_back(effect);

	effect->Play(resource);

	return effect;
}

void EffectManager::StopAll()
{
	for (auto& effect : mActiveEffects)
	{
		effect->Stop();
		effect->GetTransform()->ChangeParent(mPoolEffectRoot->GetTransform());

		mPoolEffects.emplace(effect);
	}

	mActiveEffects.clear();
}

void EffectManager::RegisterEffect(std::shared_ptr<Resource::ResourceBase> effect)
{
	mResources.try_emplace(effect->GetPath(), effect);
}
