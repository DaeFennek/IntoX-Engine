#include "InputHandler.h"
#include <iostream>


InputHandler::InputHandler(IntoXWindow *pIntoXWindow) : window(pIntoXWindow) {}

InputHandler::~InputHandler()
{
	std::cout << "InputHandler dctr called" << std::endl;
}

int InputHandler::HandleInput(SDL_Event *sdlEvent)
{	
	return 0;
}
