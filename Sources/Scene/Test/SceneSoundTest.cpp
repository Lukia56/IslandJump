#include "SceneSoundTest.h"
#include "SceneSelectDebug.h"
#include "System/InputManager.h"
#include "System/ResourceManager.h"
#include "System/SoundManager.h"
#include "System/Input/Keyboard.h"
#include "System/Resource/Sound.h"

namespace
{
	const char* const kBGMPath = "Resources\\Sound\\BGM\\TestBGM.ogg";
	const char* const kSoundPath = "Resources\\Sound\\SE\\TestSE.wav";
}

SceneSoundTest::SceneSoundTest()
{

}

void SceneSoundTest::OnInit()
{
	mSound = ResourceManager::GetInstance().GetResource<Resource::Sound>(kSoundPath);

	std::shared_ptr<Resource::ResourceBase> bgm = ResourceManager::GetInstance().GetResource<Resource::Sound>(kBGMPath);
	SoundManager::GetInstance().PlayBGM(bgm);
}

std::unique_ptr<SceneBase> SceneSoundTest::OnUpdate()
{
	if (InputManager::GetInstance().IsPressed(Input::Action::Submit))
	{
		SoundManager::GetInstance().PlaySe(mSound);
	}

	if (Keyboard::GetInstance().IsDown(KEY_INPUT_Q))
	{
		return std::make_unique<SceneSelectDebug>();
	}

	return nullptr;
}
