#pragma once
#include "IEventHandler.h"
#include "IntoXWindow.h"

class KeyboardHandler : public IEventHandler
{
	public:
		KeyboardHandler(class IntoXWindow *pWindow);
		virtual ~KeyboardHandler();
		virtual bool HandleEvent(SDL_Event *sdlEvent);
	protected:
		bool m_keymap[283];
	private:
		bool HandleKeyDown(SDL_Event *pSdlEvent);
		bool HandleKeyUp(SDL_Event *pSdlEvent);
		class IntoXWindow *m_pWindow;	

};
