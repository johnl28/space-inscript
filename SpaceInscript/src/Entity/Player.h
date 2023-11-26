#pragma once
#include "Actor.h"


class Player: public Actor
{
public:
	Player() : Actor(1, PLAYER_CHAR)
	{
	}

	void OnCollide(Actor* otherActor) override;
};

