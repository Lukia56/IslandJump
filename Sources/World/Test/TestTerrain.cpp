#include "TestTerrain.h"
#include "Collision/Collision3D.h"
#include "Collision/CollisionTag.h"
#include "World/Component/Collider3D.h"

TestTerrain::TestTerrain(const Vector3& size) :
	mCollider(nullptr)
{
	mCollider = std::make_unique<Collider3D>(
		std::make_unique<Collision::AABB3D>(size),
		this,
		Collision::Tag::Body
	);
}

void TestTerrain::Init()
{
	SetTag(Tag::Terrain);
}

void TestTerrain::Update()
{
}

void TestTerrain::DebugDraw()
{
	mCollider->GetShape()->DebugDraw();
}
