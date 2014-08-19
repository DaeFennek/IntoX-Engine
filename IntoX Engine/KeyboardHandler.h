#ifndef __KEYBOARDHANDLER_H__
#define __KEYBOARDHANDLER_H__

#include "InputHandler.h"


class KeyboardHandler : public InputHandler
{
	public:
		KeyboardHandler(IntoXWindow *pIntoXWindow);
		virtual ~KeyboardHandler();
		virtual int HandleInput(SDL_Event *sdlEvent);
	protected:
	private:
		int HandleKeyDown(SDL_Event *sdlEvent);
		int HandleKeyUp(SDL_Event *sdlEvent);

};

#endif //__KEYBOARDHANDLER_H__