#pragma once
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include "EventSubscriber.h"
using namespace std;
enum EventType
{
	ON_W_DOWN,

	ON_A_DOWN,

	ON_S_DOWN,

	ON_D_DOWN,

	ON_E_DOWN,

	ON_Q_DOWN,


	////Always leave at the end/////
	NUM_EVENTS
};
class Event
{
public:
	bool m_isOn;
	EventType m_eventType;
	vector<EventSubscriber> m_subscribers;
	
	Event(EventType _eventType);
	~Event();
	void addSubscriber(EventSubscriber _eventSubscriber);
	void Trigger();
	//add functions that has to be executed as their are subscribed to the event
};

