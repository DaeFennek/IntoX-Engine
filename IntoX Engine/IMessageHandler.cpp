#include "IMessageHandler.h"
#include "Engine.h"

IMessageHandler::IMessageHandler()
{
	Engine::Get().AddBroadcaster(*this);
}

IMessageHandler::~IMessageHandler()
{
	
}
