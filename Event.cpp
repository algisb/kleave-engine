#include "Event.h"


Event::Event(EventType _eventType)
{
	m_eventType = _eventType;
	m_isOn = false;
}


Event::~Event()
{
}

void Event::addSubscriber(EventSubscriber _eventSubscriber)
{
	m_subscribers.push_back(_eventSubscriber);
}

void Event::Trigger()
{
	for (int i = 0; i < m_subscribers.size();i++)
	{
		m_subscribers[i].post();
	}
}

