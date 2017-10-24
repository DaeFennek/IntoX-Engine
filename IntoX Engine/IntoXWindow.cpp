#include "IntoXWindow.h"
#include "OpenGLHelper.h"
#include <vector>
#include "Model.h"
#include "Entity.h"
#include "OpenGLMasterRenderer.h"
#include "Loader.h"
#include "ShaderAttributeLocationBinder.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Texture.h"
#include "Frustrum.h"

IntoXWindow::~IntoXWindow() 
{
	
}

IntoXWindow::IntoXWindow(std::string caption, int width, int height) :  m_Caption(caption), m_Height(height), m_Width(width)
{	
	
}

void IntoXWindow::Show() 
{
	if (m_SDLWindowPtr)
	{
		return;
	}	
	
	m_SDLWindowPtr = SDL_CreateWindow(m_Caption.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_Width, m_Height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (!m_SDLWindowPtr)
	{		
		DebugLog::Print( "Could not create window :  " + std::string(SDL_GetError()), DebugLog::ERROR_LOG);		
		return;
	}

	m_glContextPtr = new OpenGLRenderContext(*m_SDLWindowPtr);
	m_glContextPtr->Init();	
}

void IntoXWindow::Quit()
{
	DebugLog::Print("Close Window", DebugLog::DEFAULT_LOG);	

	if (m_glContextPtr)
	{
		Engine::Get().Stop();
		delete m_glContextPtr;		
	}

	if (m_SDLWindowPtr)
	{
		SDL_DestroyWindow(m_SDLWindowPtr);
	}			
}

void IntoXWindow::HandleMessage(const Message& msg)
{
	switch (msg.GetType())
	{
	case MSG_CLOSE_WINDOW:
		Quit();
		break;
	}
}

void IntoXWindow::OnResize()
{	
	SDL_GetWindowSize(m_SDLWindowPtr, &m_Width, &m_Height);
}

int IntoXWindow::GetWidth() const
{
	return m_Width;
}


int IntoXWindow::GetHeight() const
{
	return m_Height;
}