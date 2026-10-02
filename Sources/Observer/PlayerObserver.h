#pragma once

#include "IObserver.h"

class Player;

namespace Observer
{
	class PlayerObserver : public IObserver
	{
	public:

		PlayerObserver(Player* player);
		~PlayerObserver() = default;

		void OnNotify(Event event) override;

	private:

		Player* mPlayer;
	};
}

