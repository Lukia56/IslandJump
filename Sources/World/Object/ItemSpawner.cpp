#include "ItemSpawner.h"
#include <DxLib.h>
#include "Utility/Color.h"

ItemSpawner::ItemSpawner(Transform* terrain) :
	mTerrain(terrain),
	mIsTriggered(false)
{
}

void ItemSpawner::Init()
{
	mTransform->localPosition = mTerrain->CalculateWorldPosition();
	mTransform->Translate(0.0f, 50.0f, 0.0f);
}

void ItemSpawner::Update()
{
}

void ItemSpawner::Draw()
{
	Vector3 pos = mTransform->CalculateWorldPosition();

	int color = mIsTriggered ? Color::green.GetAsHexRGB() : Color::red.GetAsHexRGB();

	DrawSphere3D(pos.GetAsDxLibVector(), 25.0f, 8, color, color, true);
}
