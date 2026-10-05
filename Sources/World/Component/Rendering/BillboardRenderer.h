#pragma once

#include "Renderer.h"

/// <summary>
/// 画像をビルボードで描画する
/// </summary>
class BillboardRenderer : public Renderer
{
public:

	BillboardRenderer(GameObject* owner, std::shared_ptr<Resource::ResourceBase> resource);
	~BillboardRenderer() = default;

	/// <summary>
	/// 画像をゲームオブジェクトのトランスフォームで描画する
	/// </summary>
	void Draw() const override;

private:

	float mTexWidth;
};
