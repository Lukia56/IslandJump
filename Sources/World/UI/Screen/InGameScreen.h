#pragma once

#include "../Core/Screen.h"

class ItemObjectManager;
class ResultRecorder;

namespace UI
{
	class InGameScreen : public Screen
	{
	public:

		InGameScreen(float maxDistance, Transform* playerTransform, ItemObjectManager* itemObjectManager, ResultRecorder* resultRecorder);
		~InGameScreen() = default;

		void Init() override;
		void Update() override;
	};
}
