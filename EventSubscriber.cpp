#include "EventSubscriber.h"


EventSubscriber::EventSubscriber(function<void()>_func)
{
	m_func = _func;
}


EventSubscriber::~EventSubscriber()
{
}

void EventSubscriber::post()
{
	m_func();
}