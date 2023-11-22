#pragma once
#include "Renderer.h"
#include "Player.h"
#include "Singleton.h"




class GameCore: public Singleton<GameCore>
{
public:
	void Initialise()
	{

	}


	void Update();

	void SpawnEnemy(int x, int y);

};

