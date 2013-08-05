/*------------------------------------------------------------------------------
| Copyright (C) 2013  Kévin Seroux <kevin.seroux@orange.fr>                    |
|                                                                              |
| GameEngine is free software: you can redistribute it and/or modify it under  |
| it under the terms of the GNU Lesser General Public License as published by  |
| the Free Software Foundation, either version 3 of the License, or (at your   |
| option) any later version.                                                   |
|                                                                              |
| GameEngine is distributed in the hope that it will be useful, but WITHOUT    |
| ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or        |
| FITNESS FOR A PARTICULAR PURPOSE.  See the Lesser GNU General Public License |
| for more details.                                                            |
|                                                                              |
| You should have received a copy of the GNU Lesser General Public License     |
| along with GameEngine.  If not, see <http://www.gnu.org/licenses/>.          |
\_____________________________________________________________________________*/

#include "GameEngine/Window/X/XWindow.h"
#include "GameEngine/Window/Window.h"
#include "GameEngine/Common/Debug/Logger.h"
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/extensions/Xinerama.h>
#include <cstring>

using namespace common;

namespace window
{

Display* XWindow::s_display;
XEvent XWindow::s_xEvent;
Atom XWindow::s_windowDestroyRequestEvent = 0;

Atom XWindow::s_wmStateAtom = 0;
Atom XWindow::s_wmStateFullScreenAtom;
XEvent XWindow::s_fullScreenEvent;

Bool windowHasEvent(Display*, XEvent* event, XPointer window)
{
    return event->xany.window == reinterpret_cast<Window>(window);
}

XWindow::XWindow(const WindowAttributes* const attributes)
{
    m_posX = attributes->posX;
    m_posY = attributes->posY;
    m_width = attributes->width;
    m_height = attributes->height;

    if(s_countInstance == 1) //If it's the first window created
    {
        s_display = XOpenDisplay(0);
        if(s_display == 0)
        {
            Logger::logError()("Failed to open X display");
            return;
        }
    }

    if(s_wmStateAtom == 0) //It's for the full screen feature
    {
        s_wmStateAtom = XInternAtom(s_display, "_NET_WM_STATE", False);
        s_wmStateFullScreenAtom = XInternAtom(s_display,
                                              "_NET_WM_STATE_FULLSCREEN",
											  False);

        s_fullScreenEvent.type = ClientMessage;
        s_fullScreenEvent.xclient.message_type = s_wmStateAtom;
        s_fullScreenEvent.xclient.format = 32;
        s_fullScreenEvent.xclient.data.l[1] = s_wmStateFullScreenAtom;
        s_fullScreenEvent.xclient.data.l[2] = 0;
    }

    //It's for the Xinerama technology (multiple monitor = 1 screen)
    int eventBase, errorBase;
    if(XineramaQueryExtension(s_display, &eventBase, &errorBase) == True)
    {
        if(XineramaIsActive(s_display) == True)
        {
            int number;
            XineramaScreenInfo* screens;
            screens = XineramaQueryScreens(s_display, &number);

            Logger::logInfo()("You have %i screens", number);
            for(uint8_t i(0); i < number; i++)
            {
                Logger::logInfo()("    Screen number: %i",
                                  screens[i].screen_number);
                Logger::logInfo()("        x: %i", screens[i].x_org);
                Logger::logInfo()("        y: %i", screens[i].y_org);
                Logger::logInfo()("        width: %i", screens[i].width);
                Logger::logInfo()("        height: %i", screens[i].height);
            }
        }
    }

    int screen = XDefaultScreen(s_display);

    if(m_width == 0)
    {
        m_width = XDisplayWidth(s_display, screen);
        Logger::logInfo()("The requested window's width is 0, setti\
                          ng to %u", m_width);
    }
    if(m_height == 0)
    {
        m_height = XDisplayHeight(s_display, screen);
        Logger::logInfo()("The requested window's height is 0, sett\
                          ing to %u", m_height);
    }

    Window parent;
    if(attributes->parent == 0)
        parent = XDefaultRootWindow(s_display);
    else
        parent = attributes->parent->m_window;

    m_window = XCreateWindow(s_display, parent, m_posX, m_posY,
                             m_width, m_height, 0,
                             DefaultDepth(s_display, screen), InputOutput,
                             DefaultVisual(s_display, screen), 0, 0);

    if(s_windowDestroyRequestEvent == 0)
        s_windowDestroyRequestEvent = XInternAtom(s_display, "WM_DELETE_WINDOW",
		                                          False);

    XSetWMProtocols(s_display, m_window, &s_windowDestroyRequestEvent, 1);

    XSelectInput(s_display, m_window, EnterWindowMask | LeaveWindowMask |
                 FocusChangeMask | PointerMotionMask | ButtonPressMask |
                 ButtonReleaseMask | KeyPressMask | KeyReleaseMask |
                 StructureNotifyMask | VisibilityChangeMask);

    XStoreName(s_display, m_window, attributes->title);

    XMapWindow(s_display, m_window);

    displayFullScreenMode(attributes->fullScreen);

    m_isVisible = true;
}

XWindow::~XWindow()
{
    destroy();
}

void XWindow::destroy()
{
    if(m_instance != 0)
    {
        XDestroyWindow(s_display, m_window);
        m_instance = 0;
        s_countInstance--;
        if(s_countInstance == 0) //If there is not more instance, we free
            XCloseDisplay(s_display);
    }
}

void XWindow::displayFullScreenMode(bool const isInFullScreen)
{
    static bool wasInFullScreen = false;

    s_fullScreenEvent.xclient.window = m_window;

    if(isInFullScreen == true)
    {
        if(wasInFullScreen == false)
            s_fullScreenEvent.xclient.data.l[0] = 1;
    }
    else
    {
        if(wasInFullScreen == true)
            s_fullScreenEvent.xclient.data.l[0] = 0;
    }

    wasInFullScreen = !wasInFullScreen;

    XSendEvent(s_display, DefaultRootWindow(s_display), False,
	           SubstructureNotifyMask, &s_fullScreenEvent);
}

void XWindow::isVisible(bool const visibility)
{
    if(visibility == true)
        if(m_isVisible == false)
            XMapWindow(s_display, m_window);
    else
        if(m_isVisible == true)
            XUnmapWindow(s_display, m_window);
    !m_isVisible;
}

bool XWindow::checkEvent()
{
    if(XCheckIfEvent(s_display, &s_xEvent, windowHasEvent,
	reinterpret_cast<XPointer>(m_window)))
        return processEvent();
    else
        return false;
}

bool XWindow::waitEvent()
{
    if(XIfEvent(s_display, &s_xEvent, windowHasEvent,
	reinterpret_cast<XPointer>(m_window)))
        return processEvent();
}

bool XWindow::processEvent()
{
    switch(s_xEvent.type)
    {
    case MotionNotify: //When the mouse move
        m_event.type = MouseMotionEvent;
        m_event.events.mouseMotion.posX = s_xEvent.xmotion.x;
        m_event.events.mouseMotion.posY = s_xEvent.xmotion.y;
        return true;

    case ButtonPress: //When a mouse's button is pressed
        m_event.type = MouseButtonEvent;
        m_event.events.mouseButton.button = s_xEvent.xbutton.button;
        m_event.events.mouseButton.isPressed = true;
        return true;

    case ButtonRelease: //When a mouse's button is released
        m_event.type = MouseButtonEvent;
        m_event.events.mouseButton.button = s_xEvent.xbutton.button;
        m_event.events.mouseButton.isPressed = false;
        return true;

    case EnterNotify: //When the window enter in the window
        m_event.type = MouseFocusEvent;
        m_event.events.mouseFocus.isFocusIn = true;
        return true;

    case LeaveNotify: //When the mouse leave of the window
        m_event.type = MouseFocusEvent;
        m_event.events.mouseFocus.isFocusIn = false;
        return true;

    case FocusIn:
        m_event.type = ActiveWindowEvent;
        m_event.events.keyboardFocus.isFocusIn = true;
        return true;

    case FocusOut:
        m_event.type = ActiveWindowEvent;
        m_event.events.keyboardFocus.isFocusIn = false;
        return true;

    case KeyPress: //When a keyboard's key is pressed
        m_event.type = KeyEvent;
        m_event.events.key.isPressed = true;
        m_event.events.key.key =
			XKeysymToString(XLookupKeysym(&s_xEvent.xkey, 0));
        return true;

    case KeyRelease: //When a keyboard's key is released
        m_event.type = KeyEvent;
        m_event.events.key.isPressed = false;
        m_event.events.key.key =
			XKeysymToString(XLookupKeysym(&s_xEvent.xkey, 0));
        return true;

    case ConfigureNotify: //When the window's position, size has changed
        if(s_xEvent.xconfigure.width != m_width ||
           s_xEvent.xconfigure.height != m_height)
        {
            m_event.type = WindowResizeEvent;
            m_width = s_xEvent.xconfigure.width;
            m_height = s_xEvent.xconfigure.height;
            m_event.events.windowResize.width = m_width;
            m_event.events.windowResize.height = m_height;
            return true;
        }
        else if(s_xEvent.xconfigure.x != m_posX ||
                s_xEvent.xconfigure.y != m_posY)
        {
            m_event.type = WindowMoveEvent;
            m_posX = s_xEvent.xconfigure.x;
            m_posY = s_xEvent.xconfigure.y;
            m_event.events.windowMove.posX = m_posX;
            m_event.events.windowMove.posY = m_posY;
            return true;
        }
        return false;

    case MapNotify:
        if(m_wasIconified == false) 
        {
            m_event.type = WindowVisibilityEvent;
            m_event.events.windowVisibility.state = WindowDeiconify;
            !m_wasIconified;
            return true;
        }
        return false;

    case UnmapNotify:
        m_wasIconified = true;
        m_event.type = WindowVisibilityEvent;
        m_event.events.windowVisibility.state = WindowIconify;
        return true;

    case VisibilityNotify:
        m_event.type = WindowVisibilityEvent;
        switch(s_xEvent.xvisibility.state)
        {
        case VisibilityUnobscured:
            m_event.events.windowVisibility.state = WindowFullyVisible;
            return true;

        case VisibilityPartiallyObscured:
            m_event.events.windowVisibility.state = WindowObstructed;
            return true;

        case VisibilityFullyObscured:
            m_event.events.windowVisibility.state = WindowHidden;
            return true;
        }
        return false;

    case ClientMessage:
            m_event.type = WindowDestroyRequestEvent;
            return true;
    }
    return false;
}

}
