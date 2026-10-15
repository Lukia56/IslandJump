#include "PlayTimerUI.h"
#include "TextObject.h"
#include "System/Resource/ResourceBase.h"
#include "World/Other/ResultRecorder.h"

namespace
{
	constexpr float kOneMinuteSec = 60.0f;
}

namespace UI
{
	PlayTimerUI::PlayTimerUI(ResultRecorder* resultRecorder, std::shared_ptr<Resource::ResourceBase> font) :
		mTimerText(nullptr),
		mResultRecorder(resultRecorder)
	{
		mTimerText = CreateToChild<UI::TextObject>(font, "", Color::white, HolizontalAlignment::Left, VerticalAlignment::Middle);
		mTimerText->GetRectTransform()->SetAnchor(RectTransform::Anchor::FullStretch);
	}

	void PlayTimerUI::Init()
	{
	}

	void PlayTimerUI::Update()
	{
		float playTime = mResultRecorder->GetPlayTime();

		int minutes = static_cast<int>(std::floor(playTime / kOneMinuteSec));
		int seconds = static_cast<int>(std::floor(playTime - minutes * kOneMinuteSec));
		int tenMilliseconds = static_cast<int>(std::floor((playTime - seconds - minutes * kOneMinuteSec) * 100.0f));

		std::string textMinutes = std::to_string(minutes);
		std::string textSeconds = (seconds < 10 ? "0" : "") + std::to_string(seconds);
		std::string textTenMilliSec = (tenMilliseconds < 10 ? "0" : "") + std::to_string(tenMilliseconds);

		std::string text = textMinutes + ": " + textSeconds + "." + textTenMilliSec;
		mTimerText->SetDisplayText(text);
	}
}
