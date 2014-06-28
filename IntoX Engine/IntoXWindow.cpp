#include "IntoXWindow.h"
#include "KeyboardHandler.h"
#include "OpenGLhelper.h"

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
		SDL_WM_SetCaption(this->caption, NULL);
		mainScreen = SDL_SetVideoMode(this->width, this->height, 32, SDL_SWSURFACE | SDL_OPENGL);
		if (mainScreen == NULL)
		{
			Quit();
		}
		
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		
		ClearMainGLBufferBuffers();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0, this->width / this->height, 1.0, 500.0);
		glViewport(0, 0, this->width, this->height);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glEnable(GL_DEPTH_TEST);
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
		ClearMainGLBufferBuffers();
		
		// test that checks that OpenGL works correnctly
		glBegin(GL_QUADS);
			glColor3d(1,0,0);
			glVertex3f(-1,-1,-10);
			glColor3d(1,1,0);
			glVertex3f(1,-1,-10);
			glColor3d(1,1,1);
			glVertex3f(1,1,-15);
			glColor3d(0,1,1);
			glVertex3f(-1,1,-15);
		glEnd();

		SDL_GL_SwapBuffers();
	}
	Quit();
}