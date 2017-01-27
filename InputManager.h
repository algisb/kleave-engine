#pragma once
#include "./SDL2/include/SDL.h"
#include <iostream>
#include "EventHandler.h"
class InputManager
{
public:
	EventHandler * m_eventHandler;
	
	InputManager(bool * _exitProgram, EventHandler * _eventHandler);
	~InputManager();
	
	void update();
private:
	bool * m_exitProgram; //main loop controller
};

