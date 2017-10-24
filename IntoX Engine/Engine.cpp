#include "Engine.h"
#include "SDLEventManager.h"
#include "IOpenGLRenderer.h"

Engine::Engine()
{
}


Engine::~Engine()
{
	if (m_pEventController)
	{
		delete m_pEventController;
	}
}

void Engine::Init()
{
	int errorCode = SDL_Init(SDL_INIT_EVERYTHING);
	if (errorCode > 0)
	{
		DebugLog::Print(std::string("Failed to initialize SDL: Error ") + std::to_string(errorCode), DebugLog::ERROR_LOG);
	}
	else
	{
		DebugLog::Print("Initialized SDL", DebugLog::DEFAULT_LOG);		
		m_pEventController = new SDLEventManager();
	}
}

void Engine::Run()
{
	m_bRun = true;

	while (m_bRun)
	{				
		m_pGLRenderContext->Render();		
		m_pEventController->Update();
	}
}

void Engine::Destroy()
{	
	m_broadcastList.clear();
	SDL_Quit();
}

void Engine::Stop()
{
	m_bRun = false;
}

void Engine::BroadcastMsg(const Message& msg)
{
	for (std::vector<IMessageHandler*>::reverse_iterator i = m_broadcastList.rbegin(); i != m_broadcastList.rend(); ++i) 
	{
		(**i).HandleMessage(msg);		
	}	
}

void Engine::AddBroadcaster(IMessageHandler& msgHandler)
{
	m_broadcastList.push_back(&msgHandler);
}

void Engine::RemoveBroadcaster(IMessageHandler& msgHandler)
{
	auto msgHandlerIt = std::find(m_broadcastList.begin(), m_broadcastList.end(), &msgHandler);
	if (msgHandlerIt != m_broadcastList.end())
		m_broadcastList.erase(msgHandlerIt);
}

void Engine::SetRenderContext(IOpenGLRenderer* glRenderContext)
{
	m_pGLRenderContext = glRenderContext;
}
