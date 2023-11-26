#pragma once
#include "Core.h"
 
// Base class for a Controller
// Controllers can posses an Actor to give it a specific behaviour
class Controller
{
public:
	virtual void Update() = 0;
};

