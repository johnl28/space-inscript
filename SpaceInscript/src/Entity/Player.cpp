#include "Player.h"
#include "Enemy.h"
#include "CoinActor.h"
#include "LevelManager.h"

void Player::OnCollide(Actor* otherActor)
{
	if (dynamic_cast<Enemy*>(otherActor))
	{
		LevelManager::GetInstance()->GameOver();
	}
	else if (dynamic_cast<CoinActor*>(otherActor))
	{
		otherActor->Destroy();
		LevelManager::GetInstance()->IncrementScore();
	}
}