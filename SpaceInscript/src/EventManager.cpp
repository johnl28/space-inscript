#include "EventManager.h"


void EventManager::Update()
{
	for (auto it = m_eventsMap.begin(); it != m_eventsMap.end();)
	{
		auto event = it->second;
		it++;

		if (event->IsDestroyed())
		{
			DeleteEvent(event.get());
			continue;
		}

		event->Update();
	}
}

void EventManager::Reset()
{
	for (auto it = m_eventsMap.begin(); it != m_eventsMap.end();)
	{
		auto event = it->second;
		it++;
		DeleteEvent(event.get());
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

