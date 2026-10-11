#pragma once

#include "../Core/Screen.h"

namespace UI
{
	class InGameScreen : public Screen
	{
	public:

		InGameScreen(float maxDistance, Transform* playerTransform);
		~InGameScreen() = default;

		void Init() override;
		void Update() override;
	};
}
