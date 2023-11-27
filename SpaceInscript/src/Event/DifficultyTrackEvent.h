#pragma once
#include "Core.h"
#include "Event.h"
#include "LevelManager.h"

class DifficultyEvent : public LoopEvent
{
public:
	DifficultyEvent(std::time_t loopIntervalMs) : LoopEvent(loopIntervalMs)
	{
	}

	void Trigger()
	{
		LevelManager::GetInstance()->IncrementDifficulty();
	}


};

