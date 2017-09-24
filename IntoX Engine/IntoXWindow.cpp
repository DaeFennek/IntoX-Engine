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

IntoXWindow::IntoXWindow(std::string caption, int width, int height) : m_Caption(caption), m_Height(height), m_Width(width) 
{	
	
}


void IntoXWindow::Init()
{	
	int errorCode = SDL_Init(SDL_INIT_EVERYTHING);
	if (errorCode > 0)
	{
		DebugLog::Print(std::string("Failed to initialize SDL: Error ") + std::to_string(errorCode), DebugLog::ERROR_LOG);
	}
	else
	{
		DebugLog::Print("Initialized SDL", DebugLog::DEFAULT_LOG);
		m_EventControllerPtr = new InputEventController(this);
	}		
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

	Run();
}

void IntoXWindow::Quit()
{
	DebugLog::Print("Close Window", DebugLog::DEFAULT_LOG);	
	
	if (m_EventControllerPtr)
	{
		delete m_EventControllerPtr;
	}

	if (m_SDLWindowPtr)
	{
		SDL_DestroyWindow(m_SDLWindowPtr);
	}
	SDL_Quit();
}


void IntoXWindow::Run()
{
	OpenGLRenderContext context(*m_SDLWindowPtr);
	if (context.Init())
	{		
		context.SetPreRenderCallback([&]() { m_EventControllerPtr->Update(); });
		context.Exec();
	}	
	

	

	/*while(bRun)
	{		
		startclock = SDL_GetTicks();		

		/*if (startclock - lastLoopUpdateTime >= 20)
		{
			bRun = m_pEventController->Update();

			const Uint8 *keys = SDL_GetKeyboardState(nullptr);

			if (keys[SDL_SCANCODE_W])
			{
				camera.UpdatePosition(glm::vec3(0.0f, -.2f, .0f));
			}
			if (keys[SDL_SCANCODE_A])
			{
				camera.UpdatePosition(glm::vec3(.2f, 0.0f, .0f));
			}
			if (keys[SDL_SCANCODE_S])
			{
				camera.UpdatePosition(glm::vec3(0.f, .2f, 0.f));
			}
			if (keys[SDL_SCANCODE_D])
			{
				camera.UpdatePosition(glm::vec3(-.2f, 0.0f, .0f));
			}

			if (keys[SDL_SCANCODE_UP])
			{
				camera.UpdatePitch(-0.5f);
			}
			if (keys[SDL_SCANCODE_LEFT])
			{
				camera.UpdateYaw(-0.5f);
			}
			if (keys[SDL_SCANCODE_DOWN])
			{
				camera.UpdatePitch(0.5f);
			}
			if (keys[SDL_SCANCODE_RIGHT])
			{
				camera.UpdateYaw(0.5f);
			}		
		}
		

		/*glm::mat4 pMtx = renderer.GetProjectionMatrix();
		glm::mat4 modelViewMtx = camera.GetViewMatrix() * entity.GetModelMatrix();

		renderer.AddEntity(entity);		

		renderer.ClearBuffers();
		shader->Start();
		shader->LoadUniformMatrix4f("viewMatrix", camera.GetViewMatrix());				
		renderer.Render(*shader);
		shader->Stop();
		renderer.ClearRenderList();
		
		//SDL_GL_SwapWindow(m_pSDLWindow);

		deltaclock = SDL_GetTicks() - startclock;
		if ( deltaclock > 0)
		{	
			currentFPS = 1000 / deltaclock;
		}
		
		SDL_SetWindowTitle(m_pSDLWindow, (m_caption + "; FPS: " + std::to_string(currentFPS)).c_str());
	}
	*/
	
//	loader.Clean();
	
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