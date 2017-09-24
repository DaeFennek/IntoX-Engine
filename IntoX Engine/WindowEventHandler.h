#pragma once

#include "IEventHandler.h"
#include "IntoXWindow.h"

class WindowEventHandler : public IEventHandler
{	

public:
	WindowEventHandler(class IntoXWindow *pWindow);
	~WindowEventHandler();
	virtual bool HandleEvent(SDL_Event *pSdlEvent);

private:
	class IntoXWindow *m_pWindow;
};

