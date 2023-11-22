#pragma once
#include "Controller.h"
#include "Core.h"
#include "Actor.h"

class PlayerController: public Controller
{
public:
	PlayerController(std::shared_ptr<Actor> actor) : Controller(actor) {}


	void Update() override
	{
		if (GetAsyncKeyState('W') & 0x8000)
		{
			m_actor->MoveUp();
		}
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			m_actor->MoveDown();
		}

	}
};

