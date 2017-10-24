#pragma once

#include "stdfax.h"
#include "OpenGLMasterRenderer.h"
#include "IOpenGLRenderer.h"
#include "Camera.h"
#include "Loader.h"
#include "ShaderProgram.h"
#include "Engine.h"

class OpenGLRenderContext : public IMessageHandler, public IOpenGLRenderer
{
public:
	OpenGLRenderContext(SDL_Window& window);
	~OpenGLRenderContext();

	bool Init() override;	
	void Render() override;


	float GetHeight() const;
	float GetWidth() const;


	virtual void HandleMessage(const Message& msg) override;

private:
	std::unique_ptr<class OpenGLMasterRenderer> m_OpenGLMasterRendererPtr;		
	SDL_GLContext m_GLContext;
	SDL_Window& m_Window;	

	unsigned int m_startclock = 0;
	unsigned int m_deltaclock = 0;
	unsigned int m_currentFPS = 0;

	// just here for testing, make dynamic later!
	Camera m_camera;
	Loader m_loader;	
	std::unique_ptr<class ShaderProgram> m_shader; 
	Entity* m_pEntity;
};

