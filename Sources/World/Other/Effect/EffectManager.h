#pragma once

#include "World/GameObject.h"
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

class EffectInstance;
namespace Resource
{
	class ResourceBase;
}

class EffectManager : public GameObject
{
public:

	EffectManager(int maxEffect);
	~EffectManager() = default;

	void Init() override;

	void Update() override;

	EffectInstance* Play(std::string filePath, const Vector3& pos);

	void StopAll();

	int GetInstanceCount() { return mActiveEffects.size(); }

	void RegisterEffect(std::shared_ptr<Resource::ResourceBase> effect);

private:

	std::unordered_map<std::string, std::shared_ptr<Resource::ResourceBase>> mResources;

	int mMaxEffect;

	GameObject* mActiveEffectRoot;

	GameObject* mPoolEffectRoot;

	std::vector<EffectInstance*> mActiveEffects;

	std::stack<EffectInstance*> mPoolEffects;
};
