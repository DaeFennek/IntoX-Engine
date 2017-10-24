#pragma once

enum EMessageType
{
	MSG_KEY_DOWN,
	MSG_KEY_UP,
	MSG_CLOSE_WINDOW,
	MSG_RESIZE_WINDOW,	
};


class Message {
public: 

	Message(EMessageType type) : m_type(type) {}

	EMessageType GetType() const
	{
		return m_type;
	}

private:
	EMessageType m_type;

};

