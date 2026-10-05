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
		switch (event)
		{
		case Observer::Event::ReachGoal:

			mPlayer->SetActive(false);
			
			break;

		case Observer::Event::FallCloudPlayer:

			mPlayer->SetActive(false);

			break;
		}
	}
}
