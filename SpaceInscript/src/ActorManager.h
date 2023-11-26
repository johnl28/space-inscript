#pragma once
#include "Entity/Actor.h"
#include "Entity/Player.h"

class ActorManager
{
public:
	void Update();
	void Reset();
	void SetPlayer(std::shared_ptr<Player> player);

	bool AddActor(std::shared_ptr<Actor> actor);
	bool DeleteActor(std::shared_ptr<Actor> actor);

	int GetActorCount() const;

private:
	void CheckPlayerCollision();

private:
	std::shared_ptr<Player> m_player;
	std::map<int, std::shared_ptr<Actor>> m_actors;

};



