#pragma once
#include "Actor.h"


class Player: public Actor
{
public:
	Player() : Actor(1, PLAYER_CHAR)
	{
		SetSpeed(0.7f);
	}

	void OnCollide(Actor* otherActor) override;

	void SetDead(bool isDead)
	{
		m_dead = isDead;
	}

	bool IsDead() const
	{
		return m_dead;
	}

private:
	bool m_dead = false;
};

