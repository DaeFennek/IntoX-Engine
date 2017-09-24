#include "OpenGLRenderContext.h"
#include "OpenGLHelper.h"
#include "OpenGLMasterRenderer.h"
#include "Loader.h"
#include "ShaderAttributeLocationBinder.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "EventManager.h"

OpenGLRenderContext::OpenGLRenderContext(SDL_Window& window) : m_Window(window)
{	
}

OpenGLRenderContext::~OpenGLRenderContext()
{
	SDL_GL_DeleteContext(m_GLContext);	
}

bool OpenGLRenderContext::Init()
{
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

	return true;
}

void OpenGLRenderContext::Exec()
{
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

	Loader loader;		

	m_OpenGLMasterRendererPtr = std::make_unique<OpenGLMasterRenderer>(this);	

	Model model = loader.CreateModel(vertices, texture, indices);
	model.SetTexture(Texture::LoadTexture("Res/wood.png"));

	ShaderAttributeLocationBinder attributeLocationBinder;
	attributeLocationBinder.AddUniform(DEFAULT_TRANSFORMATION_MATRIX);
	attributeLocationBinder.AddUniform(DEFAULT_VIEW_MATRIX);
	attributeLocationBinder.AddUniform(DEFAULT_PROJECTION_MATRIX);
	//attributeLocationBinder.Add(1, "position");s
	//attributeLocationBinder.Add(0, "color");

	auto shader = ShaderProgram::Create("VertexShader.glsl", "FragmentShader.glsl", &attributeLocationBinder);
	Entity entity(&model, glm::vec3(.0f, 0.0f, -10.0f), glm::vec3(.0f, .0f, .0f), glm::vec3(1.0f, 1.0f, 1.0f));

	Camera camera;
	camera.SetPosition(glm::vec3(.0f, .0f, .0f));
		
	unsigned int startclock = 0;
	unsigned int deltaclock = 0;
	unsigned int currentFPS = 0;	

	m_bRender = true;
	
	WindowClosedEvent::Listener windowClosedEventListener;
	windowClosedEventListener.Observe(EventManger::Get().m_WindowClosedEvent, [&](int x) { m_bRender = false; });

	while (m_bRender)
	{
		startclock = SDL_GetTicks();
		glm::mat4 pMtx = m_OpenGLMasterRendererPtr->GetProjectionMatrix();
		glm::mat4 modelViewMtx = camera.GetViewMatrix() * entity.GetModelMatrix();

		m_OpenGLMasterRendererPtr->AddEntity(entity);

		m_OpenGLMasterRendererPtr->ClearBuffers();
		shader->Start();
		shader->LoadUniformMatrix4f("viewMatrix", camera.GetViewMatrix());
		
		// todo use separate thread for updating input
		m_PreRenderCallback();

		m_OpenGLMasterRendererPtr->Render(*shader);	

		m_PostRenderCallback();

		shader->Stop();
		m_OpenGLMasterRendererPtr->ClearRenderList();

		SDL_GL_SwapWindow(&m_Window);

		deltaclock = SDL_GetTicks() - startclock;
		if (deltaclock > 0)
		{
			currentFPS = 1000 / deltaclock;
		}
		
		SDL_SetWindowTitle(&m_Window, ("IntoX Engine; FPS: " + std::to_string(currentFPS)).c_str());	
	}

	loader.Clean();
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
