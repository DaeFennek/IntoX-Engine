#include "IOpenGLRenderer.h"
#include "Engine.h"

IOpenGLRenderer::IOpenGLRenderer()
{
}


IOpenGLRenderer::~IOpenGLRenderer()
{
}

bool IOpenGLRenderer::Init()
{
	ENGINE.SetRenderContext(this);	
	return true;
}
