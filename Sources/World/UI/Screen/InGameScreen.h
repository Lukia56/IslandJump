#pragma once

#include "../Core/Screen.h"

class ItemObjectManager;
class ResultRecorder;

namespace UI
{
	class ItemEffectTextManager;

	class InGameScreen : public Screen
	{
	public:

		InGameScreen(float maxDistance, Transform* playerTransform, Transform* cloudTransform, ItemObjectManager* itemObjectManager, ResultRecorder* resultRecorder);
		~InGameScreen() = default;

		void Init() override;
		void Update() override;

	public:

		ItemEffectTextManager* GetItemEffectTextManager() const { return mItemEffectTextManager; }

	private:

		ItemEffectTextManager* mItemEffectTextManager;
	};
}
