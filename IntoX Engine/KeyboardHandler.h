#pragma once

#include "Engine.h"
#include "KeyMessage.h"

class KeyboardHandler
{
	public:
		KeyboardHandler() {}
		~KeyboardHandler() {}

		void HandleKeyDown(SDL_Event *pSdlEvent)
		{
			ENGINE_BROADCAST(KeyMessage(MSG_KEY_DOWN, SDL_GetKeyboardState(nullptr)));
		}

		void HandleKeyUp(SDL_Event *pSdlEvent)
		{
			ENGINE_BROADCAST(KeyMessage(MSG_KEY_UP, SDL_GetKeyboardState(nullptr)));
		}
};
