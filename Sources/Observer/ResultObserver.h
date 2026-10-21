#pragma once

#include "IObserver.h"

class ResultRecorder;
class CameraManager;
class DeathCloud;
class Transform;
namespace UI
{
	class UIManager;
}

namespace Observer
{
	class ResultObserver : public IObserver
	{
	public:

		ResultObserver(ResultRecorder* resultRecorder, UI::UIManager* uiManager, CameraManager* cameraManager, DeathCloud* deathCloud);
		ResultObserver(ResultRecorder* resultRecorder, UI::UIManager* uiManager, Transform* playerTransform);
		~ResultObserver() = default;

		void OnNotify(Event event) override;

	private:

		ResultRecorder* mResultRecorder;

		UI::UIManager* mUIManager;

		CameraManager* mCameraManager;

		DeathCloud* mDeathCloud;
	};
}
