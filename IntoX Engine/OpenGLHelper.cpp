#include "OpenGLhelper.h"

void ClearMainGLBufferBuffers()
{
	glClearColor(1.0f, 1.f, 1.f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}