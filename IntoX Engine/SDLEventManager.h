#pragma once

#include "Engine.h"
#include "WindowEventHandler.h"
#include "KeyboardHandler.h"

class SDLEventManager
{

public:
	SDLEventManager()
	{
		
	}

	~SDLEventManager()
	{
		
	}

	void Update()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{			
			// special events
			switch (event.type)
			{
			case SDL_WINDOWEVENT:
				m_windowEventHandler.HandleEvent(&event);
				break;
			case SDL_KEYDOWN:
				m_keyboardEventHandler.HandleKeyDown(&event);
				break;

			case SDL_KEYUP:
				m_keyboardEventHandler.HandleKeyUp(&event);
				break;
			case SDL_QUIT:
				ENGINE_BROADCAST(Message(MSG_CLOSE_WINDOW));
				break;
			
			}
		}
	}

private:
	KeyboardHandler m_keyboardEventHandler;
	WindowEventHandler m_windowEventHandler;
};

