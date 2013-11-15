/*------------------------------------------------------------------------------
| DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE                                  |
| Version 2, December 2004                                                     |
|                                                                              |
| Copyright (C) 2013  Kévin Seroux <kevin.seroux@orange.fr>                    |
|                                                                              |
| Everyone is permitted to copy and distribute verbatim or modified copies of  |
| this license document, and changing it is allowed as long as the name is     |
| changed.                                                                     |
|                                                                              |
| DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE                                  |
| TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION              |
|                                                                              |
| 0. You just DO WHAT THE FUCK YOU WANT TO.                                    |
\-----------------------------------------------------------------------------*/

#include "GameEngine/Window/Window.h"
#include "GameEngine/Window/Event.h"
#include "GameEngine/Window/BaseImplWindow.h"
#include "GameEngine/Common/Debug/Logger.h"
#include <GL/GL.h>

using namespace window;
using namespace common;

int main()
{
    bool isEnd = false;

    WindowAttributes attributes;
	
    attributes.title = "Title";
    attributes.parent = 0;
	attributes.iconURL = "Cursor_White.cur";
    attributes.fullScreen = false;
    attributes.posX = 0;
    attributes.posY = 0;
    attributes.width = 800;
    attributes.height = 600;
	attributes.show = true;
	attributes.displayCursor = true;
	unsigned char glVersions[3] = {45, 30, 21};
	attributes.openGLVersion = glVersions;
	attributes.version = 3;

	try
	{
		GLRenderWindow myWindow(&attributes);
		const Event* myEvent = myEvent = myWindow.getEventStructure();
		float green = 0;
		float blue = 0;
	
		while(myWindow.isAlive())
		{
			myWindow.checkEvent();

			switch(myEvent->type)
			{
			/*case KeyDownEvent: //To do
				Logger::logInfo()("A key has been pressed");
				break;

			case KeyUpEvent: //To do
				Logger::logInfo()("A key has been released");
				break;

			case MouseButtonEvent: //To improve
				if(myEvent->events.mouseButton.isPressed == true)
					Logger::logInfo()("Mouse button %u pressed",
					                  myEvent->events.mouseButton.button);
				else
					Logger::logInfo()("Mouse button %u released",
					                  myEvent->events.mouseButton.button);
				break;

			case MouseLeaveEvent:
				Logger::logInfo()("Mouse is outside the client area");
				break;*/

			case MouseMotionEvent:
				Logger::logInfo()("Cursor position(%u,%u)",
					              myEvent->events.mouseMotion.posX,
								  myEvent->events.mouseMotion.posY);
				green = (float)myEvent->events.mouseMotion.posX / myWindow.getWidth();
				blue = (float)myEvent->events.mouseMotion.posY / myWindow.getHeight();
				break;

			/*case FocusInWindowEvent: //Does not work
				Logger::logInfo()("The window has the focus");
				break;

			case FocusOutWindowEvent: //Does not work
				Logger::logInfo()("The window has not the focus");
				break;*/

			/*case WindowMoveEvent: //Does not work
				Logger::logInfo()("New window's position(%u, %u)",
				                  myEvent->events.windowMove.posX,
								  myEvent->events.windowMove.posY);
				break;

			case WindowResizeEvent: //Work only with maximize/minimize button
				Logger::logInfo()("New window's size(%u, %u)",
				                  myEvent->events.windowResize.width,
								  myEvent->events.windowResize.height);
				break;

			case WindowHiddenEvent: //Does not work
				Logger::logInfo()("Window hidden");
				break;

			case WindowFullyVisibleEvent: //Does not work
				Logger::logInfo()("Window fully visible");
				break;

			case WindowDestroyRequestEvent:
				myWindow.destroy();
				break;*/
			}
		
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(1, green, blue, 0);
			myWindow.swapBuffers();
		}
	}
	catch(exception::PixelFormatNotFound& ex)
	{
		Logger::logError()("Unable to find a pixel format in file %s at line %u"
						   , ex.file, ex.line);
	}
	catch(exception::BadOpenGLVersion& ex)
	{
		Logger::logError()("You have tried to use a unsupported OpenGL %u.%u "
		                   "version", ex.minorVersion, ex.majorVersion); 
	}

    return 0;
}
