#pragma once
#include "Actor.h"

class Enemy: public Actor
{
public:
	Enemy(int id) : Actor(id, ENEMY_CHAR)
	{

	}


	void OnUpdate() override
	{
		if (GetX() + GetWidth() < 0)
		{
			Destroy();
		}
	}
};

