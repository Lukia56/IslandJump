#include "TestCollider.h"
#include "Collision/Collision3D.h"
#include "../Component/Collider3D.h"

TestCollider::TestCollider(std::unique_ptr<Collision::IShape3D> shape) :
	mCollider(nullptr)
{
	mCollider = std::make_unique<Collider3D>(std::move(shape), this, Collision::Tag::Body);
}

void TestCollider::Init()
{

}

void TestCollider::Update()
{

}

void TestCollider::DebugDraw()
{
	mCollider->GetShape()->DebugDraw();
}
