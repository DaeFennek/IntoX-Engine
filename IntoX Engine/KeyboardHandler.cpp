#include "KeyboardHandler.h"
#include <iostream>



KeyboardHandler::KeyboardHandler(IntoXWindow *pIntoXWindow) : InputHandler(pIntoXWindow)
{

}

KeyboardHandler::~KeyboardHandler() 
{
	std::cout << "KeyboardHandler dctr called" << std::endl;
}



int KeyboardHandler::HandleInput(SDL_Event *sdlEvent) 
{
	int status = 0;
	while(SDL_PollEvent(sdlEvent))
	{
		switch (sdlEvent->key.type)
		{
			case SDL_QUIT:
				// ptr to window and call destructor				
				status = 1;
				break;

			case SDL_KEYDOWN:
				status = this->HandleKeyDown(sdlEvent);
				break;

			case SDL_KEYUP:
				status = this->HandleKeyUp(sdlEvent);
				break;
		}
	}
	return status;
}

int KeyboardHandler::HandleKeyDown(SDL_Event *sdlEvent) 
{
	int status = 0;
	switch (sdlEvent->key.keysym.sym)
	{
		case SDLK_ESCAPE:
			// ptr to window and call destructor
			status = true;
			break;
		
	}
	return status;

}

int KeyboardHandler::HandleKeyUp(SDL_Event *sdlEvent)
{
	// TODOs
	return 0;
}
