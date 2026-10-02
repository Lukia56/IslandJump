#include "PlayerObserver.h"
#include "World/Character/Player.h"

namespace Observer
{
	PlayerObserver::PlayerObserver(Player * player) :
		mPlayer(player)
	{
	}

	void PlayerObserver::OnNotify(Event event)
	{
		if (event == Event::ReachGoal)
		{
			mPlayer->SetActive(false);
		}
	}
}
