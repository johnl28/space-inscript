#include "Player.h"
#include "Enemy.h"
#include "CoinActor.h"
#include "GameCore.h"

void Player::OnCollide(Actor* otherActor)
{
	if (dynamic_cast<Enemy*>(otherActor))
	{
		GameCore::GetInstance()->GameOver();
	}
	else if (dynamic_cast<CoinActor*>(otherActor))
	{
		otherActor->Destroy();
		GameCore::GetInstance()->IncrementScore();
	}
}