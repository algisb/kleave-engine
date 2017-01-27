#include "EventHandler.h"


EventHandler::EventHandler()
{
	for (int i = 0; i < NUM_EVENTS;i++)
	{
		m_events.push_back((EventType)i);
	}
}


EventHandler::~EventHandler()
{
}

Event * EventHandler::getEvent(EventType _eventType)
{
	for (int i = 0; i < m_events.size();i++)
	{
		if (m_events[i].m_eventType == _eventType)
		{
			return &m_events[i];
		}
	}
	perror("Get event error, undefined event");
	system("pause");
	exit(0);
}

void EventHandler::update()
{
	for (int i = 0; i < m_events.size();i++)
	{
		if (m_events[i].m_isOn)
		{
			m_events[i].Trigger(); //TODO add to event queue instead of trigger 
		}
	}
}
