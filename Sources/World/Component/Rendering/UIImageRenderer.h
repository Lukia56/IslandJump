#pragma once

#include "Renderer.h"
#include "Utility/Math.h"

class RectTransform;

/// <summary>
/// 矩形を使用してUI画像の描画を行う
/// </summary>
class UIImageRenderer : public Renderer
{
public:

	UIImageRenderer(GameObject* owner, std::shared_ptr<Resource::ResourceBase> resource, RectTransform* rectTransform, float alpha = 1.0f);
	~UIImageRenderer() = default;

	/// <summary>
	/// 画像をゲームオブジェクトのトランスフォームで描画する
	/// </summary>
	void Draw() const override;

public:

	void SetResource(std::shared_ptr<Resource::ResourceBase> resource) override;

	/// <summary>
	/// スケーリングしたテクスチャのサイズを取得する
	/// </summary>
	Vector2 GetTexSize() const;

	/// <summary>
	/// アルファを0.0から1.0の範囲で指定する
	/// </summary>
	void SetAlpha(float alpha) { mAlpha = Math::Clamp(alpha, 0.0f, 1.0f); }
	float GetAlpha() const { return mAlpha; }

private:

	Vector2 mTexSize;

	float mAlpha;

	RectTransform* mRectTransform;
};
