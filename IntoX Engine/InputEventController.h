#pragma once

#include "IEventHandler.h"

class InputEventController
{

public:
	InputEventController(class IntoXWindow *pWindow);
	~InputEventController();
	bool Update();

private:
	class IEventHandler *m_pKeyboardEventHandler;
	class IEventHandler *m_pWindowEventHandler;
	class IntoXWindow *m_pWindow;
	
};

