#include "IntoXWindow.h"
#include "KeyboardHandler.h"

IntoXWindow::~IntoXWindow() 
{
	std::cout << "Window destructor called" << std::endl;
	// Todo: to be continue .. 

	if (this->keyboardHandler != NULL)
		delete this->keyboardHandler;
}

IntoXWindow::IntoXWindow(char* pCaption, int pWidth, int pHeight) : caption(pCaption), height(pHeight), width(pWidth) {}


int IntoXWindow::Init()
{
	int sdlInitCode = SDL_Init(SDL_INIT_EVERYTHING);
	if (sdlInitCode > 0)
	{
		return sdlInitCode;
	}

	this->keyboardHandler = new KeyboardHandler(this);
}

void IntoXWindow::Hide() 
{

}

void IntoXWindow::Show() 
{
	// if mainScreen not created then create
	if (mainScreen != NULL)
	{
		mainScreen = SDL_SetVideoMode(this->width, this->height, 32, SDL_SWSURFACE | SDL_OPENGL);
		if (mainScreen == NULL)
		{
			Quit();
		}
	}

	this->Run();
}

void IntoXWindow::Quit()
{
	std::cout << "Close called" << std::endl;
	SDL_Quit();
}

void IntoXWindow::Run()
{
	SDL_Event sdlEvent;
	bool keepRunning = true;
	while(keepRunning)
	{
		if (this->keyboardHandler->HandleInput(&sdlEvent) > 0)
			keepRunning = false;
	}
	Quit();
}