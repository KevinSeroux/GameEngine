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
#include "GameEngine/Common/Debug/Logger.h"

using namespace window;
using namespace common;

int main()
{
    bool isEnd = false;
	RenderWindow myWindow("Window 1", false, 400, 400, 800, 600);
	RenderWindow myWindow2("Window 2", false, 400, 400, 800, 600);
	const Event* const myEvent = myWindow.getEventStructure();
	const Event* const myEvent2 = myWindow2.getEventStructure();

	while(!isEnd)
    {
        if(myWindow.exist() && myWindow.checkEvent())
        {
            Logger::logInfo()("    Window 1");
            if(myEvent->type == MouseFocusEvent)
            {
                if(myEvent->events.mouseFocus.isFocusIn == true)
                    Logger::logInfo()("        Has the mouse focus");
                else
                    Logger::logInfo()("        Has not the mouse focus");
            }
            else if(myEvent->type == ActiveWindowEvent)
            {
                if(myEvent->events.keyboardFocus.isFocusIn == true)
                    Logger::logInfo()("        Has the keyboard focus");
                else
                    Logger::logInfo()("        Has not the keyboard focus");
            }
            else if(myEvent->type == MouseMotionEvent)
            {
                Logger::logInfo()("        Cursor position(%u,%u)",
                                  myEvent->events.mouseMotion.posX,
                                  myEvent->events.mouseMotion.posY);
            }
            else if(myEvent->type == WindowMoveEvent)
            {
                Logger::logInfo()("        New position(%u,%u)",
                                  myEvent->events.windowMove.posX,
                                  myEvent->events.windowMove.posY);
            }
            else if(myEvent->type == WindowResizeEvent)
            {
                Logger::logInfo()("        New size(%u,%u)",
                                  myEvent->events.windowResize.width,
                                  myEvent->events.windowResize.height);
            }
            else if(myEvent->type == MouseButtonEvent)
            {
                if(myEvent->events.mouseButton.isPressed == true)
                {
                    Logger::logInfo()("        Button %u is pressed",
                                      myEvent->events.mouseButton.button);
                }
                else
                    Logger::logInfo()("        Button %u is released",
                                      myEvent->events.mouseButton.button);
            }
            else if(myEvent->type == WindowVisibilityEvent)
            {
                switch(myEvent->events.windowVisibility.state)
                {
                case WindowFullyVisible:
                    Logger::logInfo()("        Window visible");
                    break;
                case WindowObstructed:
                    Logger::logInfo()("        Window obstructed");
                    break;
                case WindowHidden:
                    Logger::logInfo()("        Window hidden");
                    break; //OUBLIE ICI
                }
            }
            else if(myEvent->type == KeyEvent)
            {
                if(myEvent->events.key.isPressed == true)
                    Logger::logInfo()("        Key pressed");
                else
                    Logger::logInfo()("        Key released");
            }
            else if(myEvent->type == WindowDestroyRequestEvent)
            {
                myWindow.destroy();
                if(RenderWindow::getCountInstance() == 0)
                    isEnd = true;
            }
        }
        else if(myWindow2.exist() && myWindow2.checkEvent())
        {
            Logger::logInfo()("    Window 2");
            if(myEvent2->type == MouseFocusEvent)
            {
                if(myEvent2->events.mouseFocus.isFocusIn == true)
                    Logger::logInfo()("        Has the mouse focus");
                else
                    Logger::logInfo()("        Has not the mouse focus");
            }
            else if(myEvent2->type == ActiveWindowEvent)
            {
                if(myEvent2->events.keyboardFocus.isFocusIn == true)
                    Logger::logInfo()("        Has the keyboard focus");
                else
                    Logger::logInfo()("        Has not the keyboard focus");
            }
            else if(myEvent2->type == MouseMotionEvent)
            {
                Logger::logInfo()("        Cursor position(%u,%u)",
                                  myEvent2->events.mouseMotion.posX,
                                  myEvent2->events.mouseMotion.posY);
            }
            else if(myEvent2->type == WindowMoveEvent)
            {
                Logger::logInfo()("        New position(%u,%u)",
                                  myEvent2->events.windowMove.posX,
                                  myEvent2->events.windowMove.posY);
            }
            else if(myEvent2->type == WindowResizeEvent)
            {
                Logger::logInfo()("        New size(%u,%u)",
                                  myEvent2->events.windowResize.width,
                                  myEvent2->events.windowResize.height);
            }
            else if(myEvent2->type == MouseButtonEvent)
            {
                if(myEvent2->events.mouseButton.isPressed == true)
                {
                    Logger::logInfo()("        Button %u is pressed",
                                      myEvent2->events.mouseButton.button);
                }
                else
                    Logger::logInfo()("        Button %u is released",
                                      myEvent2->events.mouseButton.button);
            }
            else if(myEvent2->type == WindowVisibilityEvent)
            {
                switch(myEvent2->events.windowVisibility.state)
                {
                case WindowFullyVisible:
                    Logger::logInfo()("        Window visible");
                    break;
                case WindowObstructed:
                    Logger::logInfo()("        Window obstructed");
                    break;
                case WindowHidden:
                    Logger::logInfo()("        Window hidden");
                    break; //OUBLIE ICI
                }
            }
            else if(myEvent2->type == KeyEvent)
            {
                if(myEvent2->events.key.isPressed == true)
                    Logger::logInfo()("        Key pressed");
                else
                    Logger::logInfo()("        Key released");
            }
            else if(myEvent2->type == WindowDestroyRequestEvent)
            {
                myWindow2.destroy();
                if(RenderWindow::getCountInstance() == 0)
                    isEnd = true;
            }
        }
    }

	return 0;
}
