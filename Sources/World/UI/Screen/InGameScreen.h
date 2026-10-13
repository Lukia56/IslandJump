#pragma once

#include "../Core/Screen.h"

class ItemObjectManager;

namespace UI
{
	class InGameScreen : public Screen
	{
	public:

		InGameScreen(float maxDistance, Transform* playerTransform, ItemObjectManager* itemObjectManager);
		~InGameScreen() = default;

		void Init() override;
		void Update() override;
	};
}
