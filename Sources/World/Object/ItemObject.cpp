#include "ItemObject.h"
#include <DxLib.h>
#include "Utility/Color.h"

namespace
{
	constexpr Vector3 kOffsetPos{ 0.0f, 75.0f, 0.0f };
}

ItemObject::ItemObject(const Vector3& spawnPos) :
	mSpawnPos(spawnPos)
{
}

void ItemObject::Init()
{
	mTransform->localPosition = mSpawnPos + kOffsetPos;
}

void ItemObject::Update()
{

}

void ItemObject::DebugDraw()
{
	Vector3 pos = mTransform->CalculateWorldPosition();

	DrawSphere3D(pos.GetAsDxLibVector(), 20.0f, 8, Color::magenta.GetAsHexRGB(), Color::magenta.GetAsHexRGB(), true);
}
