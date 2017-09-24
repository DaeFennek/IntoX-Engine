#include "InputEventController.h"
#include "WindowEventHandler.h"
#include "KeyboardHandler.h"
#include "EventManager.h"

InputEventController::InputEventController(class IntoXWindow *pWindow) : m_pWindow(pWindow)
{
	m_pWindowEventHandler = new WindowEventHandler(pWindow);
	m_pKeyboardEventHandler = new KeyboardHandler(pWindow);
}


InputEventController::~InputEventController()
{
	delete m_pKeyboardEventHandler;
	delete m_pWindowEventHandler;
}

bool InputEventController::Update()
{	
	SDL_Event event;
	while (SDL_PollEvent(&event)) 
	{
		bool bStatus = true;

		// special events
		switch (event.type)				
		{
			case SDL_WINDOWEVENT:
				bStatus = m_pWindowEventHandler->HandleEvent(&event);
				break;

			case SDL_QUIT:				
				bStatus = false;
				EventManger::Get().m_WindowClosedEvent.Notify(0);
				break;			
		}	


		if (!bStatus)
		{
			return false;
		}
	}
	
	return true;
}
