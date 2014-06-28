#include "OpenGLhelper.h"

void ClearMainGLBufferBuffers()
{
	glClearColor(.0f, 0.f, 0.f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}