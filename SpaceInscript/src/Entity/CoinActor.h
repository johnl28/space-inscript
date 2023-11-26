#pragma once
#include "Actor.h"

class CoinActor : public Actor
{
public:
	CoinActor(int id) : Actor(id, COIN_CHAR)
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

