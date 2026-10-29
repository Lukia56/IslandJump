#include "PlayerModelAnimator.h"
#include "System/InputManager.h"
#include "System/PlayerDataManager.h"
#include "World/Character/Player.h"

PlayerModelAnimator::PlayerModelAnimator(Player* player, ModelRenderer* renderer, float fps) :
	ModelAnimator(renderer, fps),
	mCurrentAnimation(PlayerAnimation::Idle),
	mPlayer(player)
{
}

void PlayerModelAnimator::Update()
{
	PlayerAnimation nextAnim = PlayerAnimation::Idle;

	if (mPlayer->OnGround())
	{
		if (InputManager::GetInstance().IsPressed(Input::Action::Jump))
		{
			nextAnim = PlayerAnimation::JumpIn;
		}
		else
		if (InputManager::GetInstance().GetAsVector3(Input::Action::Move) != Vector3::Zero)
		{
			nextAnim = PlayerAnimation::Run;
		}
		else
		if (mCurrentAnimation == PlayerAnimation::JumpLoop
		|| (mCurrentAnimation == PlayerAnimation::Land && IsPlaying()))	// ‹­§Ä¶‚¾‚ÆRun‚âJumpIn‚ªÄ¶‚Å‚«‚È‚­‚È‚é‚½‚ß•Ê“r•ªŠò
		{
			nextAnim = PlayerAnimation::Land;
		}
	}
	else
	{
		nextAnim = PlayerAnimation::JumpLoop;
	}

	if (mCurrentAnimation != nextAnim)
	{
		mCurrentAnimation = nextAnim;

		Play(PlayerDataManager::GetInstance().GetAnimationParam(nextAnim));
	}

	ModelAnimator::Update();
}
