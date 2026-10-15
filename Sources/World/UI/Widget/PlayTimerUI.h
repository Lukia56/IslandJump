#pragma once

#include "../Core/UIObject.h"

class ResultRecorder;
namespace Resource
{
	class ResourceBase;
}

namespace UI
{
	class TextObject;

	class PlayTimerUI :public UIObject
	{
	public:

		PlayTimerUI(ResultRecorder* resultRecorder, std::shared_ptr<Resource::ResourceBase> font);
		~PlayTimerUI() = default;

		void Init() override;

		void Update() override;

	private:

		TextObject* mTimerText;

		ResultRecorder* mResultRecorder;
	};
}
