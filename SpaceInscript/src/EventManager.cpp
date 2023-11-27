#include "EventManager.h"


void EventManager::Update()
{
	for (auto it = m_eventsMap.begin(); it != m_eventsMap.end();)
	{
		auto event = it->second;
		it++;

		if (event->IsDestroyed())
		{
			DeleteEvent(event);
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
		DeleteEvent(event);
	}
}

bool EventManager::DeleteEvent(std::shared_ptr<Event> gameEvent)
{
	auto it = m_eventsMap.find(gameEvent->GetID());
	if (it == m_eventsMap.end())
	{
		return false;
	}

	m_eventsMap.erase(it);
	return true;
}

void EventManager::QueueEvent(std::shared_ptr<Event> gameEvent)
{
	++m_eventID;

	gameEvent->SetID(m_eventID);
	m_eventsMap.emplace(m_eventID, gameEvent);
}

int EventManager::GetEventsCount() const
{
	return to_int(m_eventsMap.size());
}

