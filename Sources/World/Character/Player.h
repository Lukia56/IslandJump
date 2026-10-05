#pragma once

#include "../GameObject.h"
#include <vector>
#include "Camera/CameraProperty.h"
#include "Utility/Vector.h"

class Collider3D;
class LandTerrainRecorder;
class ItemObjectManager;
namespace Observer
{
	class IObserver;
}

class Player : public GameObject
{
public:

	Player();
	Player(ItemObjectManager* itemObjectManager);

	void Init() override;

	void Update() override;

	void PhysicsUpdate() override;

	void Draw() override;

	void DebugDraw() override;

	void ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider) override;

public:

	LandTerrainRecorder* GetLandTerrainRecorder() const { return mLandTerrainRecorder.get(); }

	Observer::IObserver* GetObserver() const { return mObserver.get(); }

	void SetCameraView(const Camera::View& view) { mCameraView = view; }

private:

	void ResolvePush();

	void MoveHorizontal(float deltaTime);

	void MoveVertical(float deltaTime);

	bool CanJump() const;

	bool CanCancelJump() const;

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

	bool mOnGround;

	std::vector<std::unique_ptr<Collider3D>> mColliders;

	std::unique_ptr<LandTerrainRecorder> mLandTerrainRecorder;

	std::unique_ptr<Observer::IObserver> mObserver;

	ItemObjectManager* mItemObjectManager;

	Camera::View mCameraView;
};
