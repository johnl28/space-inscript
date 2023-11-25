﻿#pragma once
#include "Actor.h"
#include "Controller/PlayerController.h"



class Player: public Actor
{
public:
	Player() : Actor(1, &PLAYER_CHAR)
	{
		Controller* playerController = new PlayerController(std::shared_ptr<Actor>(this));

		SetController(playerController);
	}
};
