#include "InputManager.h"


InputManager::InputManager(bool * _exitProgram, EventHandler * _eventHandler)
{
	this->m_exitProgram = _exitProgram;
	this->m_eventHandler = _eventHandler;
}

InputManager::~InputManager()
{
}

void InputManager::update()
{
	SDL_Event incomingEvent;

	while (SDL_PollEvent(&incomingEvent))
	{

		switch (incomingEvent.type)
		{
		case SDL_QUIT:
			*m_exitProgram = true;
			break;
		//on mouse down
		case SDL_MOUSEBUTTONDOWN:
			switch (incomingEvent.button.button)
			{
			case 1:
				//std::cout << "m1 up" << std::endl;
				break;
			}
			break;
		//on mouse up
		case SDL_MOUSEBUTTONUP:
			switch (incomingEvent.button.button)
			{
			case 1:
				//std::cout << "m1 down" << std::endl;
				break;
			}
			break;

		//on key down
		case SDL_KEYDOWN:

			switch (incomingEvent.key.keysym.sym)
			{

			case SDLK_ESCAPE:
				*m_exitProgram = true;
				break;
			case SDLK_w:
				m_eventHandler->getEvent(ON_W_DOWN)->m_isOn = true;
				break;
			case SDLK_a:
				m_eventHandler->getEvent(ON_A_DOWN)->m_isOn = true;
				break;
			case SDLK_s:
				m_eventHandler->getEvent(ON_S_DOWN)->m_isOn = true;
				break;
			case SDLK_d:
				m_eventHandler->getEvent(ON_D_DOWN)->m_isOn = true;
				break;
			case SDLK_e:
				m_eventHandler->getEvent(ON_E_DOWN)->m_isOn = true;
				break;
			case SDLK_q:
				m_eventHandler->getEvent(ON_Q_DOWN)->m_isOn = true;
				break;
			}
			break;
		//on key up
		case SDL_KEYUP:

			switch (incomingEvent.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				break;
			case SDLK_w:
				m_eventHandler->getEvent(ON_W_DOWN)->m_isOn = false;
				break;
			case SDLK_a:
				m_eventHandler->getEvent(ON_A_DOWN)->m_isOn = false;
				break;
			case SDLK_s:
				m_eventHandler->getEvent(ON_S_DOWN)->m_isOn = false;
				break;
			case SDLK_d:
				m_eventHandler->getEvent(ON_D_DOWN)->m_isOn = false;
				break;
			case SDLK_e:
				m_eventHandler->getEvent(ON_E_DOWN)->m_isOn = false;
				break;
			case SDLK_q:
				m_eventHandler->getEvent(ON_Q_DOWN)->m_isOn = false;
				break;
			}
			break;
		}
	}
}
