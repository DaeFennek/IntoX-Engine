#pragma once

#include <vector>
#include "stdfax.h"
#include "Message.h"
#include "IMessageHandler.h"

#define ENGINE Engine::Get()
#define ENGINE_BROADCAST(msg) Engine::Get().BroadcastMsg(msg)

class Engine
{

private:
	~Engine();
	Engine();

public:	
	void Init();
	void Run();	
	void Destroy();
	void Stop();
	void BroadcastMsg(const Message& msg);
	void AddBroadcaster(IMessageHandler& msgHandler);
	void RemoveBroadcaster(IMessageHandler& msgHandler);
	void SetRenderContext(class IOpenGLRenderer* glRenderContext);

	static Engine& Get()
	{
		static Engine obj;
		return obj;
	}

private:
	class IOpenGLRenderer* m_pGLRenderContext;
	class SDLEventManager* m_pEventController;
	std::vector<IMessageHandler*> m_broadcastList;
	bool m_bRun;
};

