#include "WindowEventHandler.h"


WindowEventHandler::WindowEventHandler(class IntoXWindow *pWindow) : m_pWindow(pWindow)
{
}


WindowEventHandler::~WindowEventHandler()
{
}

bool WindowEventHandler::HandleEvent(SDL_Event *pSdlEvent)
{
	switch (pSdlEvent->window.event)
	{
		case SDL_WINDOWEVENT_RESIZED:
			m_pWindow->OnResize();
			break;

	}

	return true;
}