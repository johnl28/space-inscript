#pragma once
#include "Core.h"
#include "Controller.h"
#include "Entity/Enemy.h"


class EnemyController: public Controller
{
public:
	EnemyController(Enemy* enemy)
	{
		m_enemy = std::shared_ptr<Enemy>(enemy);
	}

	void Update()
	{
		auto i = rand() % 100;
		if (i > 99)
		{
			m_enemy->MoveLeft();
		}

		m_enemy->MoveLeft();
	}

private:
	std::shared_ptr<Enemy> m_enemy;
};

