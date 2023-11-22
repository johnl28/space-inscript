#pragma once
#include "Core.h"
 
class Actor;

class Controller
{
public:
	Controller(std::shared_ptr<Actor> actor): m_actor(actor) {}

	virtual void Update() = 0;

protected:
	std::shared_ptr<Actor> m_actor;
};

