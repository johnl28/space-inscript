#pragma once
#include "Core.h"

struct InputEvent {

};

typedef void (*InputSubscription)(const InputEvent*);


class InputManager
{
public:
	void OnUpdate();
	void SubscribeToInputEvent(InputSubscription subscription);

private:
	std::vector<InputSubscription> m_subscriptions;
};

