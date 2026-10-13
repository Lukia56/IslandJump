#include "ItemSpawner.h"
#include <DxLib.h>
#include "Collision/Collision3D.h"
#include "Utility/Color.h"
#include "../Character/LandTerrainRecorder.h"
#include "../Component/Collider3D.h"
#include "../Component/EffectAnimator.h"
#include "../Other/ItemObjectManager.h"
#include "System/TimeManager.h"

namespace
{
	constexpr float kTriggerRadius = 250.0f;

	constexpr float kEffectDuration = 2.0f;

	const char* const kEffectPath = "Resources\\Effect\\ItemSpawnerEffect.efk";
}

ItemSpawner::ItemSpawner(Transform* terrain, LandTerrainRecorder* landTerrainRecorder, ItemObjectManager* itemObjectManager) :
	mTerrain(terrain),
	mIsTriggered(false),
	mEffectTimer(0.0f),
	mCollider(nullptr),
	mEffectAnimator(nullptr),
	mLandTerrainRecorder(landTerrainRecorder),
	mItemObjectManager(itemObjectManager)
{
}

void ItemSpawner::Init()
{
	SetTag(Tag::ItemSpawner);

	mTransform->localPosition = mTerrain->CalculateWorldPosition();
	mTransform->Translate(0.0f, 50.0f, 0.0f);

	mCollider = std::make_unique<Collider3D>(
		std::make_unique<Collision::Sphere3D>(kTriggerRadius),
		this,
		Collision::Tag::Sensor
	);

	mEffectAnimator = std::make_unique<EffectAnimator>(this, kEffectPath);
}

void ItemSpawner::Update()
{
	Vector3 worldPos = mTransform->CalculateWorldPosition();

	mCollider->GetShape()->SetPosition(worldPos);

	if (!mIsTriggered)
	{
		mEffectTimer -= TimeManager::GetDeltaTime();
		if (mEffectTimer < 0.0f)
		{
			mEffectAnimator->Stop();
			mEffectAnimator->Play();

			mEffectTimer = kEffectDuration;
		}
	}

	mEffectAnimator->Update();
}

void ItemSpawner::DebugDraw()
{
	mCollider->GetShape()->DebugDraw();
}

void ItemSpawner::ResolveCollision(const Collision::Result& result, const Collider3D* myCollider, const Collider3D* oppCollider)
{
	if (oppCollider->GetOwner()->GetTag() != GameObject::Tag::Player) return;

	if (!IsPlayerLandedMyself()) return;
	if (!mLandTerrainRecorder->GetPreLandTerrain()) return;

	mIsTriggered = true;

	mCollider->Disable();
	mEffectAnimator->Stop();

	Vector3 preTerrainPos = mLandTerrainRecorder->GetPreLandTerrain()->CalculateWorldPosition();
	mItemObjectManager->CreateItem(preTerrainPos);
}

bool ItemSpawner::IsPlayerLandedMyself() const
{
	return mTerrain == mLandTerrainRecorder->GetCurrentTerrain();
}
