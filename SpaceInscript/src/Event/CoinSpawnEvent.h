#pragma once
#include "Core.h"
#include "Event.h"
#include "LevelManager.h"

class CoinSpawnEvent : public LoopEvent
{
public:
	CoinSpawnEvent(std::time_t loopIntervalMs) : LoopEvent(loopIntervalMs)
	{
	}

	void Trigger()
	{
		LevelManager::GetInstance()->SpawnRandomCoin();
	}


};

