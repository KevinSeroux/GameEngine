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
#include "MyGLRender.h"
#include <GL/GL.h>

using namespace common;
using namespace window;

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
		MyGLRender myWindow;
		myWindow.start(&attributes);
		
		while(myWindow.isAlive())
		{
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(1, myWindow.getGreen(), myWindow.getBlue(), 0);
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