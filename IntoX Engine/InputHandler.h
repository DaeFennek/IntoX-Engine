#ifndef __INPUTHANDLER_H__
#define __INPUTHANDLER_H__

#include <SDL.h>
#include "IntoXWindow.h"


class InputHandler
{

	public:
		InputHandler(IntoXWindow *pIntoXWindow);
		virtual ~InputHandler();
		virtual int HandleInput(SDL_Event *sdlEvent);

	protected:	
		IntoXWindow *window; // don't destroy it - parsed as ctor param!!!

	private:


};


#endif //__INPUTHANDLER_H__