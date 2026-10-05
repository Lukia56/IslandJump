#pragma once

#include "Renderer.h"

/// <summary>
/// 画像の描画を行う
/// </summary>
class SpriteRenderer : public Renderer
{
public:

	SpriteRenderer(GameObject* owner, std::shared_ptr<Resource::ResourceBase> resource);
	~SpriteRenderer() = default;

	/// <summary>
	/// 画像をゲームオブジェクトのトランスフォームで描画する
	/// </summary>
	void Draw() const override;

public:

	void SetResource(std::shared_ptr<Resource::ResourceBase> resource) override;

private:

	Vector2 mTexHalfSize;
};

