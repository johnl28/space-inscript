#include "EventManager.h"


void EventManager::Update()
{
	for (auto it : m_eventsMap)
	{
		auto event = it.second;

		if (event->IsDestroyed())
		{
			DeleteEvent(event.get());
			continue;
		}

		event->Update();
	}
}

bool EventManager::DeleteEvent(Event* event)
{
	auto it = m_eventsMap.find(event->GetID());
	if (it == m_eventsMap.end())
	{
		return false;
	}

	m_eventsMap.erase(it);
	return true;
}

void EventManager::QueueEvent(Event* gameEvent)
{
	++m_eventID;

	gameEvent->SetID(m_eventID);
	m_eventsMap.emplace(m_eventID, gameEvent);
}

int EventManager::GetEventsCount() const
{
	return m_eventsMap.size();
}

