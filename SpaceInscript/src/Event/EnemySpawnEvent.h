#pragma once
#include "Core.h"
#include "Event.h"
#include "GameCore.h"


class EnemySpawnEvent: public LoopEvent
{
public:
	EnemySpawnEvent(std::time_t loopIntervalMs, std::shared_ptr<GameCore> gameCore): LoopEvent(loopIntervalMs)
	{
		m_gameCore = gameCore;
	}

	void Trigger()
	{
		m_gameCore->SpawnRandomEnemy();
	}

private:
	std::shared_ptr<GameCore> m_gameCore;
};

