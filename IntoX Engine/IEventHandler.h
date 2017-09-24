#pragma once

#include <SDL.h>

class IEventHandler
{
	public:		
		virtual bool HandleEvent(SDL_Event *pSdlEvent) = 0;
};

