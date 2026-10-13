#pragma once

#include "../GameObject.h"
#include <vector>
#include "PlayerAnimation.h"
#include "Camera/CameraProperty.h"
#include "Param/Param.h"
#include "Utility/Vector.h"

class ModelRenderer;
class ModelAnimator;
class Collider3D;
class LandTerrainRecorder;
class ItemObjectManager;
namespace Resource
{
	class ResourceBase;
}
namespace Observer
{
	class IObserver;
	class Subject;
}

class Player : public GameObject
{
public:

	Player(std::shared_ptr<Resource::ResourceBase> model, std::vector<AnimationParam> animationParams, ItemObjectManager* itemObjectManager);
	~Player() = default;

	void Init() override;

	void Update() override;

	void PhysicsUpdate() override;

	void Draw() override;

	void DebugDraw() override;

	void ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider) override;

public:

	LandTerrainRecorder* GetLandTerrainRecorder() const { return mLandTerrainRecorder.get(); }

	Observer::IObserver* GetObserver() const { return mObserver.get(); }
	Observer::Subject* GetEventSubject() const { return mEventSubject.get(); }

	void SetCameraView(const Camera::View& view) { mCameraView = view; }

private:

	void ResolvePush();

	void MoveHorizontal(float deltaTime);

	void MoveVertical(float deltaTime);

	void AnimationUpdate();

	bool CanJump() const;

	bool CanCancelJump() const;

	/// <summary>
	/// éÊìæÇ…é∏îsÇµÇΩÇÁåxçêÇï\é¶Ç∑ÇÈ
	/// </summary>
	const AnimationParam& GetAnimationParam(PlayerAnimation anim) const;

private:

	Vector3 mVelocity;

	Vector3 mLastMoveVec;

	Vector3 mCollisionPush;

	float mJumpBufferTimer;

	float mForceJumpTimer;

	bool mIsJumping;

	float mBonusJumpForce;

	float mBonusMoveSpeed;

	float mBonusMoveAccel;

	float mAerialControl;

	bool mOnGround;

	PlayerAnimation mCurrentAnimation;

	std::vector<AnimationParam> mAnimationParams;

	std::unique_ptr<ModelRenderer> mModel;

	std::unique_ptr<ModelAnimator> mModelAnimator;

	std::vector<std::unique_ptr<Collider3D>> mColliders;

	std::unique_ptr<LandTerrainRecorder> mLandTerrainRecorder;

	std::unique_ptr<Observer::IObserver> mObserver;
	std::unique_ptr<Observer::Subject> mEventSubject;

	ItemObjectManager* mItemObjectManager;

	Camera::View mCameraView;
};
