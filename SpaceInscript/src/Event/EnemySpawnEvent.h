#pragma once
#include "Core.h"
#include "Event.h"
#include "LevelManager.h"

class EnemySpawnEvent: public LoopEvent
{
public:
	EnemySpawnEvent(std::time_t loopIntervalMs): LoopEvent(loopIntervalMs)
	{
	}

	void Trigger()
	{
		auto game = LevelManager::GetInstance();

		game->SpawnRandomEnemy();
	}


};

