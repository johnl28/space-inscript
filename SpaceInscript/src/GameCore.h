#pragma once

#include "ActorManager.h"
#include "EventManager.h"

#include "Entity/Player.h"




class GameCore
{
public:
	GameCore(int width, int height);

	void Initialise();
	void Update();

	void StartGame();

	EventManager* GetEventManager();
	ActorManager* GetActorManager();
	Player* GetPlayer();
	void SpawnRandomEnemy();

private:
	void CreateSpawnEvent();

	void SpawnEnemy(int x, int y);
	bool SpawnPlayer(int x, int y);

private:
	int m_worldWidth;
	int m_worldHeight;

	std::shared_ptr<Player> m_player;

	std::shared_ptr<EventManager> m_eventManager;
	std::shared_ptr<ActorManager> m_actorManager;

};

