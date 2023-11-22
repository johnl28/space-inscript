#pragma once
#include "Core.h"
#include "Actor.h"
#include "Controller/AIController.h"

class Enemy: public Actor
{
public:
	Enemy(int id) : Actor(id, ENEMY_CHAR)
	{
		Controller* aiController = new AIController(std::shared_ptr<Actor>(this));

		SetController(aiController);
	}

};

