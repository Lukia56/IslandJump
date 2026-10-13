#pragma once

#include "IObserver.h"
#include <array>
#include <memory>

namespace Resource
{
	class ResourceBase;
}

namespace Observer
{
	class SoundObserver : public IObserver
	{
	public:

		enum class Sound
		{
			MenuSubmit,
			MenuCancel,
			MenuMoveCursor,
			Jump,
			Goal,
			ItemAppear,
			ItemObtain,
			Length,
		};

	public:

		SoundObserver();
		~SoundObserver() = default;

		void OnNotify(Event event) override;

	private:

		std::array<std::shared_ptr<Resource::ResourceBase>, static_cast<size_t>(Sound::Length)> mSounds;
	};
}
