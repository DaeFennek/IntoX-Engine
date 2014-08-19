#ifndef __INTOXWINDOWS_H__
#define __INTOXWINDOWS_H__

#include <SDL.h>
#include <SDL_opengl.h>
#include <gl\GLU.h>
#include <iostream>

// forward decleration of class InputHandler because of circular include
class InputHandler;

class IntoXWindow
{
	public:
		IntoXWindow(char* pCaption, int pWidth, int pHeight);
		~IntoXWindow();
		int Init();
		void Show();
		void Hide();
		void Quit();

	protected:
		int width;
		int height;
		char* caption;		
		//SDL_Surface* mainScreen;
		SDL_Window *window;
		SDL_GLContext context;
		InputHandler *keyboardHandler;

	private:
		void Run();

};


#endif //__INTOXWINDOWS_H__