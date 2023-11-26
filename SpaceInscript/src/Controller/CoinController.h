#pragma once
#include "Core.h"
#include "Controller.h"
#include "Entity/CoinActor.h"


class CoinController : public Controller
{
public:
	CoinController(CoinActor* coin)
	{
		m_coin = std::shared_ptr<CoinActor>(coin);
	}

	void Update()
	{
		m_coin->MoveLeft();
	}

private:
	std::shared_ptr<CoinActor> m_coin;
};

