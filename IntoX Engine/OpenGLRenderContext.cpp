#include "OpenGLRenderContext.h"
#include "OpenGLHelper.h"
#include "ShaderAttributeLocationBinder.h"
#include "KeyMessage.h"

OpenGLRenderContext::OpenGLRenderContext(SDL_Window& window) : m_Window(window)
{	
}

OpenGLRenderContext::~OpenGLRenderContext()
{
	m_loader.Clean();
	SDL_GL_DeleteContext(m_GLContext);	
}

bool OpenGLRenderContext::Init()
{
	IOpenGLRenderer::Init();

	m_GLContext = SDL_GL_CreateContext(&m_Window);

	DebugLog::Print("OpenGL " + GetOpenGLVersion(), DebugLog::DEFAULT_LOG);

	GLenum glewState = glewInit();

	if (glewState != GLEW_OK)
	{
		DebugLog::Print("Could not init glew " + std::string(reinterpret_cast<const char*>(glewGetErrorString(glewState))), DebugLog::ERROR_LOG);		
		return false;
	}

	// disable vsync.
	SDL_GL_SetSwapInterval(0);

	float v[] = {
		-0.5f, 0.5f, 0, // top left 0
		-0.5f, -0.5f, 0, // bottom left 1
		0.5f, -0.5f, 0,  // bottom right 2
		0.5f, 0.5f, .0f, // top right 3
		0.5f, 0.5f, -1.0f, // top right behind 4
		0.5f, -0.5f, -1.0f,  // bottom right behind 5
		-0.5f, -0.5f, -1.0f, // bottom left behind 6
		-0.5f, 0.5f, -1.0f, // top left behind 7

		-0.5f, 0.5f, 0, // top left 8
		-0.5f, 0.5f, -1.0f, // top left behind 9
		0.5f, 0.5f, -1.0f, // top right behind 10		
		0.5f, 0.5f, .0f, // top right 11

		-0.5f, -0.5f, 0, // bottom left 12
		-0.5f, -0.5f, -1.0f, // bottom left behind 13
		0.5f, -0.5f, -1.0f,  // bottom right behind 14
		0.5f, -0.5f, 0,  // bottom right 15

	};


	float t[] = {
		0, 0,
		0, 1,
		1, 1,
		1, 0,

		0, 0,
		0, 1,
		1, 1,
		1, 0,

		0, 0,
		0, 1,
		1, 1,
		1, 0,

		0, 0,
		0, 1,
		1, 1,
		1, 0
	};

	unsigned int i[] = {
		0, 1, 3, // front
		3, 2, 1,

		0, 6, 1, // left
		0, 6, 7,

		3, 2, 4, // right
		4, 2, 5,

		7, 4, 6, // backside
		4, 5, 6,

		8, 9, 10, // top
		8, 10, 11,

		12, 13, 14, // bottom
		12, 14, 15
	};

	std::vector<float> vertices(std::begin(v), std::end(v));
	std::vector<unsigned int> indices(std::begin(i), std::end(i));
	std::vector<float> texture(std::begin(t), std::end(t));	

	m_OpenGLMasterRendererPtr = std::make_unique<OpenGLMasterRenderer>(this);

	auto& model = m_loader.CreateModel(vertices, texture, indices);
	model.SetTexture(Texture::LoadTexture("Res/wood.png"));

	ShaderAttributeLocationBinder attributeLocationBinder;
	attributeLocationBinder.AddUniform(DEFAULT_TRANSFORMATION_MATRIX);
	attributeLocationBinder.AddUniform(DEFAULT_VIEW_MATRIX);
	attributeLocationBinder.AddUniform(DEFAULT_PROJECTION_MATRIX);

	m_shader = ShaderProgram::Create("VertexShader.glsl", "FragmentShader.glsl", attributeLocationBinder);
	m_pEntity = new Entity(&model, glm::vec3(.0f, 0.0f, -10.0f), glm::vec3(.0f, .0f, .0f), glm::vec3(1.0f, 1.0f, 1.0f));

	m_camera.SetPosition(glm::vec3(.0f, .0f, .0f));
	
	return true;
}


void OpenGLRenderContext::Render()
{
	m_startclock = SDL_GetTicks();

	m_OpenGLMasterRendererPtr->AddEntity(*m_pEntity);
	m_OpenGLMasterRendererPtr->ClearBuffers();

	m_shader->Start();
	m_shader->LoadUniformMatrix4f("viewMatrix", m_camera.GetViewMatrix());

	m_OpenGLMasterRendererPtr->Render(*m_shader);

	m_shader->Stop();
	m_OpenGLMasterRendererPtr->ClearRenderList();

	SDL_GL_SwapWindow(&m_Window);

	m_deltaclock = SDL_GetTicks() - m_startclock;
	if (m_deltaclock > 0)
	{
	m_currentFPS = 1000 / m_deltaclock;
	}

	SDL_SetWindowTitle(&m_Window, ("IntoX Engine; FPS: " + std::to_string(m_currentFPS)).c_str());
}

float OpenGLRenderContext::GetHeight() const
{						 
	int h = 0;
	SDL_GetWindowSize(&m_Window, nullptr, &h);
	return h;
}

float OpenGLRenderContext::GetWidth() const
{
	int w = 0;
	SDL_GetWindowSize(&m_Window, &w, nullptr);
	return w;
}

void OpenGLRenderContext::HandleMessage(const Message& msg)
{	
	// just for testing
	switch (msg.GetType())
	{
	case MSG_KEY_DOWN:
	case MSG_KEY_UP:
		auto& keyMsg = static_cast<const KeyMessage&>(msg);	
		auto& keymap = keyMsg.m_keys;
		if (keymap[SDL_SCANCODE_W])
		{
			m_camera.UpdatePosition(glm::vec3(0.0f, -.2f, .0f));
		}
		if (keymap[SDL_SCANCODE_A])
		{
			m_camera.UpdatePosition(glm::vec3(.2f, 0.0f, .0f));
		}
		if (keymap[SDL_SCANCODE_S])
		{
			m_camera.UpdatePosition(glm::vec3(0.f, .2f, 0.f));
		}
		if (keymap[SDL_SCANCODE_D])
		{
			m_camera.UpdatePosition(glm::vec3(-.2f, 0.0f, .0f));
		}
		if (keymap[SDL_SCANCODE_UP])
		{
			m_camera.UpdatePitch(-0.5f);
		}
		if (keymap[SDL_SCANCODE_LEFT])
		{
			m_camera.UpdateYaw(-0.5f);
		}
		if (keymap[SDL_SCANCODE_DOWN])
		{
			m_camera.UpdatePitch(0.5f);
		}
		if (keymap[SDL_SCANCODE_RIGHT])
		{
			m_camera.UpdateYaw(0.5f);
		}
		break;
	}
}
