#pragma once
#include "Core.h"
#include "Controller.h"
#include "Actor.h"


class AIController: public Controller
{
public:
	AIController(std::shared_ptr<Actor> actor) : Controller(actor) {}

	void Update()
	{
		m_actor->MoveLeft();
	}
};

