#include "SoundObserver.h"
#include "Param/Param.h"
#include "System/ResourceManager.h"
#include "System/SoundManager.h"
#include "System/Resource/Sound.h"
#include "Utility/Data/CSV/CsvLoader.h"

namespace
{
	const char* const kSoundDataPath = "Resources\\MasterData\\SoundData.csv";
}

namespace Observer
{
	SoundObserver::SoundObserver()
	{
		mSounds.fill(nullptr);

		std::vector<SoundData> soundData = Data::Csv::LoadCsvAs<SoundData>(kSoundDataPath);

		//for (int i = 0; i < static_cast<int>(Sound::Length); i++)
		for (int i = 0; i < static_cast<int>(3); i++)
		{
			std::shared_ptr<Resource::ResourceBase> sound = ResourceManager::GetInstance().GetResource<Resource::Sound>(soundData[i].filePath);
			mSounds[i] = sound;
		}
	}

	inline void SoundObserver::OnNotify(Event event)
	{
		switch (event)
		{
		case Observer::Event::UISubmit:
			SoundManager::GetInstance().PlaySe(mSounds[static_cast<size_t>(Sound::MenuSubmit)]);
			break;

		case Observer::Event::UICancel:
			SoundManager::GetInstance().PlaySe(mSounds[static_cast<size_t>(Sound::MenuCancel)]);
			break;

		case Observer::Event::UIMoveCursor:
			SoundManager::GetInstance().PlaySe(mSounds[static_cast<size_t>(Sound::MenuMoveCursor)]);
			break;
		}
	}
}
