#include "OpenGLHelper.h"

std::string GetOpenGLVersion()
{		
	return std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
}