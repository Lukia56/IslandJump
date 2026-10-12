#pragma once

#include "../GameObject.h"

class GoalTrigger;
class ModelRenderer;
class ModelAnimator;
namespace Resource
{
	class ResourceBase;
}

/// <summary>
/// ƒS[ƒ‹‚Ìƒ‚ƒfƒ‹•`‰æ‚ÆƒS[ƒ‹”»’è‚ğs‚¤
/// </summary>
class GoalObject : public GameObject
{
public:

	GoalObject();
	GoalObject(std::shared_ptr<Resource::ResourceBase> model);
	~GoalObject() = default;

	void Init() override;

	void Update() override;

	void Draw() override;

public:

	GoalTrigger* GetTrigger() const { return mTrigger; }

private:

	GoalTrigger* mTrigger;

	std::unique_ptr<ModelRenderer> mModel;

	std::unique_ptr<ModelAnimator> mAnimator;
};
