#pragma once
#include "Singleton.h"

#include "Entity/Actor.h"
#include "Entity/Player.h"

class ActorManager
{
public:
	void Update();

	bool AddActor(std::shared_ptr<Actor> actor);
	bool DeleteActor(std::shared_ptr<Actor> actor);

	int GetActorCount() const;

private:
	std::map<int, std::shared_ptr<Actor>> m_actors;

};



