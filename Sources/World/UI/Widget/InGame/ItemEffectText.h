#pragma once

#include "World/UI/Core/UIObject.h"
#include "World/Object/Item/ItemType.h"

namespace Resource
{
	class ResourceBase;
}

namespace UI
{
	class TextObject;

	class ItemEffectText : public UIObject
	{
	public:

		ItemEffectText(std::shared_ptr<Resource::ResourceBase> font);

		void Init() override;

		void Update() override;

		void Setup(ItemType itemType);

	public:

		float GetAlpha() const { return mAlpha; }

	private:

		float mAlpha;

		TextObject* mText;
	};
}
