#pragma once
#include "Singleton.h"

#include "Actor.h"
#include "Renderer.h"
#include "Player.h"

class ActorManager: public Singleton<ActorManager>
{
public:
	void Update();

	bool AddActor(std::shared_ptr<Actor> actor);
	bool DeleteActor(std::shared_ptr<Actor> actor);

private:
	std::map<int, std::shared_ptr<Actor>> m_actors;

};

