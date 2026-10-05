#pragma once

#include "../GameObject.h"

class Collider3D;
class BillboardRenderer;
namespace Resource
{
	class ResourceBase;
}

/// <summary>
/// プレイヤーが取得できる配置されたアイテム
/// </summary>
class ItemObject : public GameObject
{
public:

	ItemObject();
	~ItemObject() = default;

	void Init() override;

	void Update() override;

	void Draw() override;

	void DebugDraw() override;

	void Setup(const Vector3& spawnPos, std::shared_ptr<Resource::ResourceBase> texture);

private:

	std::unique_ptr<Collider3D> mCollider;

	std::unique_ptr<BillboardRenderer> mBillboard;
};
