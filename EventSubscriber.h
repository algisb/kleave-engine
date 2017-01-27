#pragma once
#include <functional>
using namespace std;
class EventSubscriber
{
public:
	function<void()>m_func;

	EventSubscriber(function<void()>_func);
	~EventSubscriber();
	void post();
};

