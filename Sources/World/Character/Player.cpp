#include "Player.h"
#include <cassert>
#include <imgui.h>
#include "LandTerrainRecorder.h"
#include "../Component/Collider3D.h"
#include "../Component/ModelAnimator.h"
#include "../Component/Rendering/ModelRenderer.h"
#include "../Object/DebugGround.h"
#include "../Other/ItemObjectManager.h"
#include "Collision/Collision3D.h"
#include "Collision/CollisionTag.h"
#include "Observer/PlayerObserver.h"
#include "Param/Param.h"
#include "System/InputManager.h"
#include "System/TimeManager.h"
#include "Utility/Math.h"

namespace
{
	constexpr float kMoveSpeed = 400.0f;
	constexpr float kMoveAccel = 60.0f;

	constexpr float kJumpForce = 1000.0f;
	constexpr float kJumpCancelThreshold = 150.0f;
	constexpr float kJumpBufferTime = 0.15f;
	constexpr float kForceJumpTime = 0.1f;

	constexpr float kAirResistanceCoef = 0.25f;

	constexpr float kGravity = 980.0f;

	constexpr Vector3 kBodyCollSize{ 100.0f, 100.0f, 100.0f };
	constexpr Vector3 kBodyCollOffset{ 0.0f, 50.0f, 0.0f };

	constexpr Vector3 kFootCollSize{ 100.0f, 10.0f, 100.0f };
	constexpr Vector3 kFootCollOffset{ 0.0f, -5.0f, 0.0f };

	constexpr Vector3 kInitScale{ 0.5f, 0.5f, 0.5f };

	constexpr float kYawLatency = 0.25;

	constexpr float kModelAnimationFPS = 30.0f;
}

Player::Player() :
	mJumpBufferTimer(0.0f),
	mForceJumpTimer(0.0f),
	mIsJumping(false),
	mBonusJumpForce(0.0f),
	mBonusMoveSpeed(0.0f),
	mBonusMoveAccel(0.0f),
	mAerialControl(0.0f),
	mOnGround(false),
	mCurrentAnimation(PlayerAnimation::Idle),
	mModel(nullptr),
	mLandTerrainRecorder(nullptr),
	mItemObjectManager(nullptr),
	mCameraView{}
{
	// ItemSpawnerManagerのコンストラクタで必要なためここで生成
	mLandTerrainRecorder = std::make_unique<LandTerrainRecorder>();

	mObserver = std::make_unique<Observer::PlayerObserver>(this);
}

Player::Player(ItemObjectManager* itemObjectManager) :
	mJumpBufferTimer(0.0f),
	mForceJumpTimer(0.0f),
	mIsJumping(false),
	mBonusJumpForce(0.0f),
	mBonusMoveSpeed(0.0f),
	mBonusMoveAccel(0.0f),
	mAerialControl(0.0f),
	mOnGround(false),
	mCurrentAnimation(PlayerAnimation::Idle),
	mModel(nullptr),
	mLandTerrainRecorder(nullptr),
	mItemObjectManager(itemObjectManager),
	mCameraView{}
{
	// ItemSpawnerManagerのコンストラクタで必要なためここで生成
	mLandTerrainRecorder = std::make_unique<LandTerrainRecorder>();

	mObserver = std::make_unique<Observer::PlayerObserver>(this);
}

Player::Player(std::shared_ptr<Resource::ResourceBase> model, std::vector<AnimationParam> animationParams, ItemObjectManager* itemObjectManager) :
	mJumpBufferTimer(0.0f),
	mForceJumpTimer(0.0f),
	mIsJumping(false),
	mBonusJumpForce(0.0f),
	mBonusMoveSpeed(0.0f),
	mBonusMoveAccel(0.0f),
	mAerialControl(0.0f),
	mOnGround(false),
	mCurrentAnimation(PlayerAnimation::Idle),
	mAnimationParams(animationParams),
	mModel(nullptr),
	mLandTerrainRecorder(nullptr),
	mItemObjectManager(itemObjectManager),
	mCameraView{}
{
	// ItemSpawnerManagerのコンストラクタで必要なためここで生成
	mLandTerrainRecorder = std::make_unique<LandTerrainRecorder>();

	mObserver = std::make_unique<Observer::PlayerObserver>(this);

	mModel = std::make_unique<ModelRenderer>(this, model);
}

void Player::Init()
{
	SetTag(Tag::Player);

	mTransform->localScale = kInitScale;

	mModelAnimator = std::make_unique<ModelAnimator>(mModel.get(), kModelAnimationFPS);
	mModelAnimator->Play(AnimationParam{ .animIndex = 3, .isLoop = true, .isForcePlay = false });

	mColliders.emplace_back(
		std::make_unique<Collider3D>(
			std::make_unique<Collision::AABB3D>(kBodyCollSize, kBodyCollOffset),
			this,
			Collision::Tag::Body
		));

	mColliders.emplace_back(
		std::make_unique<Collider3D>(
			std::make_unique<Collision::AABB3D>(kFootCollSize, kFootCollOffset),
			this,
			Collision::Tag::Foot
		));

	CreateToChild<DebugGround>();
}

void Player::Update()
{
	float deltaTime = TimeManager::GetDeltaTime();

	ResolvePush();

	MoveHorizontal(deltaTime);
	MoveVertical(deltaTime);

	AnimationUpdate();

	// 角度を設定する
	if (mLastMoveVec != Vector3::Zero)
	{
		float targetYaw = std::atan2(mLastMoveVec.x, mLastMoveVec.z) + Math::kPi;
		float yawDiff = targetYaw - mTransform->CalculateWorldRotation().y;
		mTransform->localRotation.y += Math::NormalizeRadian(yawDiff) * kYawLatency;
	}

	if (!mOnGround && mJumpBufferTimer > 0.0f) mJumpBufferTimer -= TimeManager::GetDeltaTime();

	if (mForceJumpTimer > 0.0f) mForceJumpTimer -= TimeManager::GetDeltaTime();
}

void Player::PhysicsUpdate()
{
	mTransform->localPosition += mVelocity * TimeManager::GetDeltaTime();

	Vector3 worldPos = mTransform->CalculateWorldPosition();
	for (const auto& collider : mColliders)
	{
		collider->GetShape()->SetPosition(worldPos);
	}

	mOnGround = false;
}

void Player::Draw()
{
	mModel->Draw();
}

void Player::DebugDraw()
{
	Vector3 pos = mTransform->CalculateWorldPosition();

	if (ImGui::Begin("Player"))
	{
		float posPtr[] = { pos.x, pos.y, pos.z };
		ImGui::InputFloat3("Position", posPtr, "%.1f");

		float velPtr[] = { mVelocity.x, mVelocity.y, mVelocity.z };
		ImGui::InputFloat3("Velocity", velPtr, "%.1f");

		ImGui::Text("OnGround: %d", mOnGround);
		ImGui::Text("IsJumping: %d", mIsJumping);

		ImGui::End();
	}

	for (const auto& collider : mColliders)
	{
		collider->GetShape()->DebugDraw();
	}
}

void Player::ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider)
{
	if (myCollider->GetTag() == Collision::Tag::Foot)
	{
		if (oppCollider->GetOwner()->GetTag() != Tag::Terrain) return;

		if (result.normal.y < 0.0f || Math::IsNearZero(result.normal.y)) return;

		// 地面との衝突
		mJumpBufferTimer = kJumpBufferTime;
		mOnGround = true;
		if (Math::IsNearZero(mVelocity.y)) mIsJumping = false;

		Transform* oppTransform = oppCollider->GetOwner()->GetTransform()->GetParent();
		mLandTerrainRecorder->UpdateLandTerrain(oppTransform);

		return;
	}

	switch (oppCollider->GetOwner()->GetTag())
	{
	case Tag::Terrain:
		mCollisionPush += result.normal * result.penetration;

		// 壁との衝突
		if (!Math::IsNearZero(result.normal.x))
		{
			mVelocity.x = 0.0f;
		}
		if (!Math::IsNearZero(result.normal.z))
		{
			mVelocity.z = 0.0f;
		}

		// 地面との衝突
		if (result.normal.y > 0.5f)
		{
			mVelocity.y = Math::Max(mVelocity.y, 0.0f);
		}
		// 天井との衝突
		if (result.normal.y < -0.5f)
		{
			mVelocity.y = Math::Min(mVelocity.y, 0.0f);
		}
		break;

	case Tag::ItemObject:

		if (mItemObjectManager)
		{
			ItemType itemType = mItemObjectManager->ConsumeItem(oppCollider->GetOwner()->GetTransform());

			switch (itemType)
			{
			case ItemType::JumpBoost:
				mBonusJumpForce += mItemObjectManager->GetEffectParam(itemType).param[0];
				break;

			case ItemType::SpeedUp:
				mBonusMoveSpeed += mItemObjectManager->GetEffectParam(itemType).param[0];
				mBonusMoveAccel += mItemObjectManager->GetEffectParam(itemType).param[1];
				break;

			case ItemType::AerialControl:
				mAerialControl += mItemObjectManager->GetEffectParam(itemType).param[0];
				mAerialControl = Math::Min(mAerialControl, 1.0f);
				break;
			}
		}

		break;
	}
}

void Player::ResolvePush()
{
	if (mCollisionPush != Vector3::Zero)
	{
		mTransform->localPosition += mCollisionPush;
		mCollisionPush = Vector3::Zero;
	}
}

void Player::MoveHorizontal(float deltaTime)
{
	float targetSpeed = kMoveSpeed + mBonusMoveSpeed;
	float accel = kMoveAccel + mBonusMoveSpeed * 0.1f;

	Vector3 moveVec = InputManager::GetInstance().GetAsVector3(Input::Action::Move);

	// カメラを正面に移動
	Vector3 forward = mCameraView.CalculatePlaneVecForward();
	Vector3 right = mCameraView.CalculatePlaneVecRight();
	moveVec = right * moveVec.x + forward * moveVec.z;

	if (moveVec != Vector3::Zero) mLastMoveVec = moveVec;

	float accelCoef = mOnGround ? 1.0f : kAirResistanceCoef + (1.0f - kAirResistanceCoef) * mAerialControl;

	// XとZ成分だけ補間させる
	Vector3 vel = Vector3(mVelocity.x, 0.0f, mVelocity.z);
	vel = vel.Approach(moveVec * targetSpeed, accel * accelCoef);

	mVelocity.x = vel.x;
	mVelocity.z = vel.z;
}

void Player::MoveVertical(float deltaTime)
{
	// ジャンプ
	if (InputManager::GetInstance().IsPressed(Input::Action::Jump) && CanJump())
	{
		mVelocity.y = kJumpForce + mBonusJumpForce;
		mIsJumping = true;
		mJumpBufferTimer = 0.0f;
		mForceJumpTimer = kForceJumpTime;
	}
	// ジャンプキャンセル
	if (!InputManager::GetInstance().IsDown(Input::Action::Jump) && CanCancelJump())
	{
		mVelocity.y = kJumpCancelThreshold;
		mIsJumping = false;
	}

	// 落下処理
	if (!mOnGround)
	{
		mVelocity.y -= kGravity * deltaTime;
	}
}

void Player::AnimationUpdate()
{
	PlayerAnimation nextAnim = PlayerAnimation::Idle;

	if (mCurrentAnimation != nextAnim)
	{
		mCurrentAnimation = nextAnim;

		mModelAnimator->Play(GetAnimationParam(nextAnim));
	}

	mModelAnimator->Update();
}

bool Player::CanJump() const
{
	return mOnGround || mJumpBufferTimer > 0.0f;
}

bool Player::CanCancelJump() const
{
	return mIsJumping && mVelocity.y > kJumpCancelThreshold && mForceJumpTimer <= 0;
}

const AnimationParam& Player::GetAnimationParam(PlayerAnimation anim) const
{
	size_t index = static_cast<size_t>(anim);

	assert(index < mAnimationParams.size() && "Player // 存在しないアニメーションデータにアクセスしました");

	return mAnimationParams[index];
}
