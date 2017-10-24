#pragma once

#include "Message.h"


class IMessageHandler
{

public:

	IMessageHandler();	
	~IMessageHandler();

	virtual void HandleMessage(const Message& msg) = 0;
};

