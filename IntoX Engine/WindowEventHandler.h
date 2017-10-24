#pragma once

#include "Engine.h"

class WindowEventHandler
{	

public:
	WindowEventHandler() {}
	~WindowEventHandler() {}

	void HandleEvent(SDL_Event *pSdlEvent)
	{
		switch (pSdlEvent->window.event)
		{
		case SDL_WINDOWEVENT_RESIZED:
			ENGINE_BROADCAST(Message(MSG_RESIZE_WINDOW));
			break;

		}		
	}
};

