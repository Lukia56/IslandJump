#include "ItemEffectTextManager.h"
#include "ItemEffectText.h"
#include "../Core/UIRoot.h"

namespace
{
	constexpr Vector3 kTextPos{ 100.0f, 50.0f, 0.0f };
}

namespace UI
{
	ItemEffectTextManager::ItemEffectTextManager(std::shared_ptr<Resource::ResourceBase> font, int maxNum) :
		mActiveRoot(nullptr),
		mPoolRoot(nullptr)
	{
		mPoolRoot = CreateToChild<UIRoot>();
		mPoolRoot->SetActive(false);

		for (int i = 0; i < maxNum; i++)
		{
			ItemEffectText* effect = mPoolRoot->CreateToChild<ItemEffectText>(font);
			mPoolTexts.emplace(effect);
		}
	}

	void ItemEffectTextManager::Init()
	{
		mActiveRoot = CreateToChild<UIRoot>();
	}

	void ItemEffectTextManager::Update()
	{
		// 再生が終了したインスタンスを削除する
		for (auto iter = mActiveTexts.begin(); iter != mActiveTexts.end();)
		{
			ItemEffectText* effect = *iter;

			if (effect->GetAlpha() > 0.0f)
			{
				iter++;
				continue;
			}

			effect->GetTransform()->ChangeParent(mPoolRoot->GetTransform());

			mPoolTexts.emplace(effect);
			iter = mActiveTexts.erase(iter);
		}
	}

	void ItemEffectTextManager::Create(ItemType itemType)
	{
		// プールから取り出す
		ItemEffectText* effect = mPoolTexts.top();

		effect->GetTransform()->ChangeParent(mActiveRoot->GetTransform());
		effect->GetTransform()->localPosition = kTextPos;
		effect->Setup(itemType);

		mPoolTexts.pop();
		mActiveTexts.emplace_back(effect);
	}
}
