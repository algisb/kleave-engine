#pragma once
#include "Event.h"
using namespace std;
class EventHandler
{
public:
	//vector<Event> m_events;
	vector<Event> m_events;

	EventHandler();
	~EventHandler();
	Event * getEvent(EventType _eventType);
	void update();
};

