#include <iostream>
#include "GameEngine/Common/Debug/Logger.h"
#include "GameEngine/Window/Window.h"

using namespace window;
using namespace common;

int main()
{
    bool isEnd = false;
	RenderWindow* myWindow = createWindow("Ma fenêtre", false, 400, 400, 800, 600);
	const Event* const myEvent = myWindow->getEventStructure();

	while(!isEnd)
    {
        if(myWindow->getEvent() == true)
        {
            if(myEvent->type == MouseFocusEvent)
            {
                if(myEvent->mouseFocus.isFocusIn == true)
                    Logger::logInfo()("    Has the mouse focus");
                else
                    Logger::logInfo()("    Has not the mouse focus");
            }
            else if(myEvent->type == KeyboardFocusEvent)
            {
                if(myEvent->keyboardFocus.isFocusIn == true)
                    Logger::logInfo()("    Has the keyboard focus");
                else
                    Logger::logInfo()("    Has not the keyboard focus");
            }
            else if(myEvent->type == MouseMotionEvent)
            {
                Logger::logInfo()("    Cursor position(%u,%u)",
                                  myEvent->mouseMotion.posX,
                                  myEvent->mouseMotion.posY);
            }
            else if(myEvent->type == WindowMoveEvent)
            {
                Logger::logInfo()("    New position(%u,%u)",
                                  myEvent->windowMove.posX,
                                  myEvent->windowMove.posY);
            }
            else if(myEvent->type == WindowResizeEvent)
            {
                Logger::logInfo()("    New size(%u,%u)",
                                  myEvent->windowResize.width,
                                  myEvent->windowResize.height);
            }
            else if(myEvent->type == MouseButtonEvent)
            {
                if(myEvent->mouseButton.isPressed == true)
                {
                    Logger::logInfo()("    Button %u is pressed",
                                      myEvent->mouseButton.button);
                }
                else
                    Logger::logInfo()("    Button %u is released",
                                      myEvent->mouseButton.button);
            }
            else if(myEvent->type == WindowVisibilityEvent)
            {
                switch(myEvent->windowVisibility.state)
                {
                case WindowVisible:
                    Logger::logInfo()("    Window visible");
                    break;
                case WindowObstructed:
                    Logger::logInfo()("    Window obstructed");
                    break;
                case WindowHidden:
                    Logger::logInfo()("    Window hidden");
                }
            }
            else if(myEvent->type == KeyEvent)
            {
                if(myEvent->key.isPressed == true)
                    Logger::logInfo()("    Key pressed");
                else
                    Logger::logInfo()("    Key released");
            }
            else if(myEvent->type == WindowDestroyEvent)
                isEnd = true;
        }
    }
    delete myWindow;

	return 0;
}
