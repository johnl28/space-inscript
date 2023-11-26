#pragma once
#include "Core.h"
#include "Event.h"
#include "GameCore.h"

class CoinSpawnEvent : public LoopEvent
{
public:
	CoinSpawnEvent(std::time_t loopIntervalMs) : LoopEvent(loopIntervalMs)
	{
	}

	void Trigger()
	{
		GameCore::GetInstance()->SpawnRandomCoin();
	}


};

