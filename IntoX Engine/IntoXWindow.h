#pragma once

#include "Engine.h"
#include "IMessageHandler.h"

class IntoXWindow : public IMessageHandler
{
	public:
		IntoXWindow(std::string caption, int width, int height);
		~IntoXWindow();
		
		void Show();		
		void Quit();		
		void OnResize();

		virtual void HandleMessage(const Message& msg) override;

		int GetWidth() const;
		int GetHeight() const;	


	protected:
		int m_Width;
		int m_Height;
		std::string m_Caption;				
		SDL_Window *m_SDLWindowPtr = nullptr;					
		class OpenGLRenderContext* m_glContextPtr = nullptr;

};
