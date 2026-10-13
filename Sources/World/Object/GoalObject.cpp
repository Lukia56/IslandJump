#include "GoalObject.h"
#include "GoalTrigger.h"
#include "../Component/ModelAnimator.h"
#include "../Component/Rendering/ModelRenderer.h"
#include "Param/Param.h"

namespace
{
	constexpr AnimationParam kAnimParam{ .animIndex = 2, .isLoop = true, .isForcePlay = false };
}

GoalObject::GoalObject() :
	mTrigger(nullptr),
	mModel(nullptr),
	mAnimator(nullptr)
{
	mTrigger = CreateToChild<GoalTrigger>();

	mModel = std::make_unique<ModelRenderer>(this, nullptr);
}

GoalObject::GoalObject(std::shared_ptr<Resource::ResourceBase> model) :
	mTrigger(nullptr),
	mModel(nullptr),
	mAnimator(nullptr)
{
	mTrigger = CreateToChild<GoalTrigger>();

	mModel = std::make_unique<ModelRenderer>(this, model);
}

void GoalObject::Init()
{
	mAnimator = std::make_unique<ModelAnimator>(mModel.get());
	mAnimator->Play(kAnimParam);

	mTransform->localRotation.y = Math::kPiOver2;
}

void GoalObject::Update()
{
	mAnimator->Update();
}

void GoalObject::Draw()
{
	mModel->Draw();
}
