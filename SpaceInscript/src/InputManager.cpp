#include "InputManager.h"



void InputManager::SubscribeToInputEvent(InputSubscription subsription)
{
	m_subscriptions.push_back(subsription);
}

void InputManager::OnUpdate()
{

}
