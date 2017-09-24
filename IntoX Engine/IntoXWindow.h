#pragma once

#include "stdfax.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include "InputEventController.h"

class IntoXWindow
{
	public:
		IntoXWindow(std::string caption, int width, int height);
		~IntoXWindow();
		void Init();
		void Show();		
		void Quit();		
		void OnResize();

		int GetWidth() const;
		int GetHeight() const;


	protected:
		int m_Width;
		int m_Height;
		std::string m_Caption;				
		SDL_Window *m_SDLWindowPtr = NULL;
		class InputEventController *m_EventControllerPtr = NULL;				

	private:
		void Run();	

};
