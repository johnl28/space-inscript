#pragma once
#include "Core.h"
#include "Event/Event.h"

class EventManager
{
public:
	void Update();

	void QueueEvent(Event *gameEvent);
	bool DeleteEvent(Event *gameEvent);
	int GetEventsCount() const;

private:
	std::map<int, std::shared_ptr<Event>> m_eventsMap;

	int m_eventID = 0;
};

