#pragma once
#include "Core.h"
#include "Event/Event.h"

class EventManager
{
public:
	void Update();
	void Reset();

	void QueueEvent(std::shared_ptr<Event> gameEvent);
	bool DeleteEvent(std::shared_ptr<Event> gameEvent);
	int GetEventsCount() const;

private:
	std::map<int, std::shared_ptr<Event>> m_eventsMap;

	int m_eventID = 0;
};

