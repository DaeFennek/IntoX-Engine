#include "KeyboardHandler.h"
#include <iostream>



KeyboardHandler::KeyboardHandler(class IntoXWindow *pWindow) : m_pWindow(pWindow)
{	
	for (unsigned short i = 0; i < sizeof(m_keymap) / sizeof(bool); i++)
	{
		m_keymap[i] = false;
	}
}

KeyboardHandler::~KeyboardHandler() 
{
	
}


bool KeyboardHandler::HandleEvent(SDL_Event *pSdlEvent)
{
	
	bool status = true;	
	switch (pSdlEvent->key.type)
	{
		case SDL_KEYDOWN:
			status = HandleKeyDown(pSdlEvent);
			break;

		case SDL_KEYUP:
			status = HandleKeyUp(pSdlEvent);
			break;
	}	
	return status;
}

bool KeyboardHandler::HandleKeyDown(SDL_Event *pSdlEvent) 
{
	bool status = true;
	
	return status;
}

bool KeyboardHandler::HandleKeyUp(SDL_Event *pSdlEvent)
{
	bool status = true;
	
	switch (pSdlEvent->key.keysym.sym)
	{
		case SDLK_ESCAPE:
			status = false;
			break;
	}

	return status;
}
