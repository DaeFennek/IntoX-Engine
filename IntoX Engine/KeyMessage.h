#pragma once

#include "Message.h"

class KeyMessage : public Message
{
public:
	KeyMessage(EMessageType type, const Uint8* keys) : Message(type), m_keys(keys) {};
	~KeyMessage(){};

	const Uint8* m_keys;
};