#include "MyGLRender.h"
#include "GameEngine/Window/Event.h"
#include "GameEngine/Common/Debug/Logger.h"

using namespace common;
using namespace window;
using namespace event;

void MyGLRender::onEvent(Event const * const p_event)
{
	switch(p_event->type)
	{
	case WindowCreatedEvent:
		Logger::logInfo()("The window is created");
		break;

	case KeyDownEvent:
		Logger::logInfo()("A key has been pressed");
		break;

	case KeyUpEvent:
		Logger::logInfo()("A key has been released");
		break;

	case KeyTextEvent:
		Logger::logInfo()("%c", p_event->events.keyText.character);
		break;

	case MouseButtonEvent:
		if(p_event->events.mouseButton.isPressed == true)
			Logger::logInfo()("Mouse button %u pressed",
						      p_event->events.mouseButton.button);
		else
			Logger::logInfo()("Mouse button %u released",
			                  p_event->events.mouseButton.button);
		break;

	case MouseLeaveEvent:
		Logger::logInfo()("Mouse is outside the client area");
		break;

	case MouseMotionEvent:
		m_green = (float)p_event->events.mouseMotion.posX / getWidth();
		m_blue = (float)p_event->events.mouseMotion.posY / getHeight();
		break;

	case FocusInWindowEvent:
		Logger::logInfo()("The window has the focus");
		break;

	case FocusOutWindowEvent:
		Logger::logInfo()("The window has no longer the focus");
		break;

	case WindowMoveEvent:
		Logger::logInfo()("New window's position(%u, %u)",
					      p_event->events.windowMove.posX,
						  p_event->events.windowMove.posY);
		break;

	case WindowResizeEvent:
		Logger::logInfo()("New window's size(%u, %u)",
					      p_event->events.windowResize.width,
						  p_event->events.windowResize.height);
		break;

	case WindowMaximizedEvent:
		Logger::logInfo()("Window maximized");
		break;

	case WindowMinimizedEvent:
		Logger::logInfo()("Window minimized");
		break;

	case WindowHiddenEvent:
		Logger::logInfo()("Window hidden");
		break;

	case WindowFullyVisibleEvent:
		Logger::logInfo()("Window fully visible");
		break;
	
	case WindowDestroyRequestEvent:
		close();
		break;
	}
}