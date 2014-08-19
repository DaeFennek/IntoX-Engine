#include "IntoXWindow.h"
#include "KeyboardHandler.h"
#include "OpenGLhelper.h"

using namespace std;

IntoXWindow::~IntoXWindow() 
{
	cout << "Window destructor called" << endl;
	// Todo: to be continue .. 

	if (this->keyboardHandler != NULL)
		delete this->keyboardHandler;
}

IntoXWindow::IntoXWindow(char* pCaption, int pWidth, int pHeight) : caption(pCaption), height(pHeight), width(pWidth) 
{
	this->window = NULL;
	this->context = NULL;
}


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
	
	if (!window)
	{
		window = SDL_CreateWindow(this->caption, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		if (!window)
		{
			cerr << "Could not create window: " << SDL_GetError();
			Quit();
		}
		context = SDL_GL_CreateContext(window);

		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);	
		
		ClearMainGLBufferBuffers();

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45., this->width / this->height, 1.0, 500.0);
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
	if (context)
	{
		SDL_GL_DeleteContext(context);
	}
	if (window)
	{
		SDL_DestroyWindow(window);
	}
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
		
		/*glClearColor(1.0f, 0.f, 0.f, 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);*/

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

		SDL_GL_SwapWindow(this->window);
		
	}
	Quit();
}