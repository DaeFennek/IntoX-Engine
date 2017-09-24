#pragma once

#include "stdfax.h"
#include "OpenGLMasterRenderer.h"
#include <functional>

class OpenGLRenderContext
{
public:
	OpenGLRenderContext(SDL_Window& window);
	~OpenGLRenderContext();

	bool Init();
	void Exec();

	inline void SetPreRenderCallback(std::function<void(void)> preRenderCallback) { m_PreRenderCallback = preRenderCallback; }
	inline void SetPostRenderCallback(std::function<void(void)> postRenderCallback) { m_PostRenderCallback = postRenderCallback; }

	float GetHeight() const;
	float GetWidth() const;

private:	
	std::unique_ptr<class OpenGLMasterRenderer> m_OpenGLMasterRendererPtr;
	bool m_bRender = false;
	SDL_GLContext m_GLContext;
	SDL_Window& m_Window;

	std::function<void(void)> m_PreRenderCallback = [](){};
	std::function<void(void)> m_PostRenderCallback = [](){};
	
};

