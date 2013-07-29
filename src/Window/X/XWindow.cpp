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
#include "GameEngine/Common/Debug/Logger.h"

using namespace common;

namespace window
{

Display* XWindow::m_display;
XEvent XWindow::m_xEvent;
Atom XWindow::m_windowDestroyRequestEvent = 0;

Bool windowHasEvent(Display*, XEvent* event, XPointer window)
{
    return event->xany.window == reinterpret_cast<Window>(window);
}

XWindow::XWindow(const char* const title, bool const isFullScreen,
                 uint16_t const posX, uint16_t const posY,
                 uint16_t const width, uint16_t const height)
{
    m_posX = posX;
    m_posY = posY;
    m_width = width;
    m_height = height;

    if(m_countInstance == 1) //If it's the first window created
    {
        m_display = XOpenDisplay(0);
        if(m_display == 0)
        {
            Logger::logError()("Failed to open X display");
            return;
        }
    }

    int screen = DefaultScreen(m_display);

    if(m_width == 0 || m_height == 0)
    {
        if(m_width == 0)
        {
            m_width = XDisplayWidth(m_display, screen);
            Logger::logInfo()("The requested window's width is 0, setti\
                                      ng to %u", m_width);
        }
        if(m_height == 0)
        {
            m_height = XDisplayHeight(m_display, screen);
            Logger::logInfo()("The requested window's height is 0, sett\
                                      ing to %u", m_height);
        }
    }

    XSetWindowAttributes attributes;

    m_window = XCreateWindow(m_display, DefaultRootWindow(m_display), posX,
                             posY, m_width, m_height, 0,
                             DefaultDepth(m_display, screen), InputOutput,
                             DefaultVisual(m_display, screen), CWBorderPixel,
                             &attributes);

    if(m_windowDestroyRequestEvent == 0)
        m_windowDestroyRequestEvent = XInternAtom(m_display, "WM_DELETE_WINDOW", False);

    XSetWMProtocols(m_display, m_window, &m_windowDestroyRequestEvent, 1);

    XSelectInput(m_display, m_window, EnterWindowMask | LeaveWindowMask |
                 FocusChangeMask | PointerMotionMask | ButtonPressMask |
                 ButtonReleaseMask | KeyPressMask | KeyReleaseMask |
                 StructureNotifyMask | VisibilityChangeMask);

    XStoreName(m_display, m_window, title);

    XMapWindow(m_display, m_window);
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
        XDestroyWindow(m_display, m_window);
        m_instance = 0;
        m_countInstance--;
        if(m_countInstance == 0) //If there is not more instance, we free
            XCloseDisplay(m_display);
    }
}

void XWindow::isVisible(bool const visibility)
{
    if(visibility == true)
        if(m_isVisible == false)
            XMapWindow(m_display, m_window);
    else
        if(m_isVisible == true)
            XUnmapWindow(m_display, m_window);
    !m_isVisible;
}

bool XWindow::checkEvent()
{
    if(XCheckIfEvent(m_display, &m_xEvent, windowHasEvent, reinterpret_cast<XPointer>(m_window)))
        return processEvent();
    else
        return false;
}

bool XWindow::waitEvent()
{
    if(XIfEvent(m_display, &m_xEvent, windowHasEvent, reinterpret_cast<XPointer>(m_window)))
        return processEvent();
}

bool XWindow::processEvent()
{
    switch(m_xEvent.type)
    {
    case MotionNotify: //When the mouse move
        m_event.type = MouseMotionEvent;
        m_event.events.mouseMotion.posX = m_xEvent.xmotion.x;
        m_event.events.mouseMotion.posY = m_xEvent.xmotion.y;
        return true;

    case ButtonPress: //When a mouse's button is pressed
        m_event.type = MouseButtonEvent;
        m_event.events.mouseButton.button = m_xEvent.xbutton.button;
        m_event.events.mouseButton.isPressed = true;
        return true;

    case ButtonRelease: //When a mouse's button is released
        m_event.type = MouseButtonEvent;
        m_event.events.mouseButton.button = m_xEvent.xbutton.button;
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
        //... XLookupKeySym()
        return true;

    case KeyRelease: //When a keyboard's key is released
        m_event.type = KeyEvent;
        m_event.events.key.isPressed = false;
        //...
        return true;

    case ConfigureNotify: //When the window's position, size has changed
        if(m_xEvent.xconfigure.width != m_width ||
           m_xEvent.xconfigure.height != m_height)
        {
            m_event.type = WindowResizeEvent;
            m_width = m_xEvent.xconfigure.width;
            m_height = m_xEvent.xconfigure.height;
            m_event.events.windowResize.width = m_width;
            m_event.events.windowResize.height = m_height;
            return true;
        }
        else if(m_xEvent.xconfigure.x != m_posX ||
                m_xEvent.xconfigure.y != m_posY)
        {
            m_event.type = WindowMoveEvent;
            m_posX = m_xEvent.xconfigure.x;
            m_posY = m_xEvent.xconfigure.y;
            m_event.events.windowMove.posX = m_posX;
            m_event.events.windowMove.posY = m_posY;
            return true;
        }

    case VisibilityNotify:
        m_event.type = WindowVisibilityEvent;
        switch(m_xEvent.xvisibility.state)
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

    case ClientMessage:
        if(m_xEvent.xclient.data.l[0] == m_windowDestroyRequestEvent)
            m_event.type = WindowDestroyRequestEvent;
        return true;
    }
    return false;
}

}
