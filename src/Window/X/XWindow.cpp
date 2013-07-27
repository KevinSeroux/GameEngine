/*------------------------------------------------------------------------------
| This file is part of GameEngine.                                             |
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

#include "XWindow.h"
#include "GameEngine/Common/Debug/Logger.h"

using namespace common;

namespace window
{

Display* XWindow::m_display = 0;

XWindow::XWindow(const char* const title, bool const isFullScreen,
                 uint16_t posX, uint16_t posY, uint16_t width, uint16_t height)
{
    m_posX = posX;
    m_posY = posY;
    m_width = width;
    m_height = height;

    if(m_display == 0)
        m_display = XOpenDisplay(0);

    if(m_display == 0)
    {
        Logger::logError()("Failed to open display");
        return;
    }

    int screen = DefaultScreen(m_display);

    if(width == 0 || height == 0)
    {
        if(width == 0)
        {
            width = XDisplayWidth(m_display, screen);
            Logger::logInfo()("The requested window's width is 0, setti\
                                      ng to %u", width);
        }
        if(height == 0)
        {
            height = XDisplayHeight(m_display, screen);
            Logger::logInfo()("The requested window's height is 0, sett\
                                      ing to %u", height);
        }
    }

    XSetWindowAttributes attributes;

    m_window = XCreateWindow(m_display, DefaultRootWindow(m_display), posX,
                             posY, width, height, 0,
                             DefaultDepth(m_display, screen), InputOutput,
                             DefaultVisual(m_display, screen), CWBorderPixel,
                             &attributes);

    m_destroyWindowEvent = XInternAtom(m_display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(m_display, m_window, &m_destroyWindowEvent, 1);

    XSelectInput(m_display, m_window, EnterWindowMask | LeaveWindowMask |
                 FocusChangeMask | PointerMotionMask | ButtonPressMask |
                 ButtonReleaseMask | KeyPressMask | KeyReleaseMask |
                 StructureNotifyMask | VisibilityChangeMask);

    XStoreName(m_display, m_window, title);

    changeVisibility();
}

void XWindow::changeVisibility()
{
    if(m_isVisible == false)
        XMapWindow(m_display, m_window);
    else
        XUnmapWindow(m_display, m_window);
    !m_isVisible;
}

bool XWindow::getEvent()
{
    if(XPending(m_display) > 0)
    {
        XNextEvent(m_display, &m_xEvent);

        switch(m_xEvent.type)
        {
        case MotionNotify: //When the mouse move
            m_event.type = MouseMotionEvent;
            m_event.mouseMotion.posX = m_xEvent.xmotion.x;
            m_event.mouseMotion.posY = m_xEvent.xmotion.y;
            return true;

        case ButtonPress: //When a mouse's button is pressed
            m_event.type = MouseButtonEvent;
            m_event.mouseButton.button = m_xEvent.xbutton.button;
            m_event.mouseButton.isPressed = true;
            return true;

        case ButtonRelease: //When a mouse's button is released
            m_event.type = MouseButtonEvent;
            m_event.mouseButton.button = m_xEvent.xbutton.button;
            m_event.mouseButton.isPressed = false;
            return true;

        case EnterNotify: //When the window enter in the window
            m_event.type = MouseFocusEvent;
            m_event.mouseFocus.isFocusIn = true;
            return true;

        case LeaveNotify: //When the mouse leave of the window
            m_event.type = MouseFocusEvent;
            m_event.mouseFocus.isFocusIn = false;
            return true;

        case FocusIn:
            m_event.type = KeyboardFocusEvent;
            m_event.keyboardFocus.isFocusIn = true;
            return true;

        case FocusOut:
            m_event.type = KeyboardFocusEvent;
            m_event.keyboardFocus.isFocusIn = false;
            return true;

        case KeyPress: //When a keyboard's key is pressed
            m_event.type = KeyEvent;
            m_event.key.isPressed = true;
            //... XLookupKeySym()
            return true;

        case KeyRelease: //When a keyboard's key is released
            m_event.type = KeyEvent;
            m_event.key.isPressed = false;
            //...
            return true;

        case ConfigureNotify: //When the window's position, size has changed
            if(m_xEvent.xconfigure.width != m_width ||
               m_xEvent.xconfigure.height != m_height)
            {
                m_event.type = WindowResizeEvent;
                m_width = m_xEvent.xconfigure.width;
                m_height = m_xEvent.xconfigure.height;
                m_event.windowResize.width = m_width;
                m_event.windowResize.height = m_height;
                return true;
            }
            else if(m_xEvent.xconfigure.x != m_posX ||
                    m_xEvent.xconfigure.y != m_posY)
            {
                m_event.type = WindowMoveEvent;
                m_posX = m_xEvent.xconfigure.x;
                m_posY = m_xEvent.xconfigure.y;
                m_event.windowMove.posX = m_posX;
                m_event.windowMove.posY = m_posY;
                return true;
            }
            return false;

        case VisibilityNotify:
            m_event.type = WindowVisibilityEvent;
            switch(m_xEvent.xvisibility.state)
            {
            case VisibilityUnobscured:
                m_event.windowVisibility.state = WindowVisible;
                return true;
            case VisibilityPartiallyObscured:
                m_event.windowVisibility.state = WindowObstructed;
                return true;
            case VisibilityFullyObscured:
                m_event.windowVisibility.state = WindowHidden;
            }

        case ClientMessage:
            if(m_xEvent.xclient.data.l[0] == m_destroyWindowEvent)
            {
                m_event.type = WindowDestroyEvent;
                XDestroyWindow(m_display, m_window);
                return true;
            }
            return false;
        }
    }
    else
        return false;
}

void XWindow::waitEvent()
{
    XNextEvent(m_display, &m_xEvent);

    switch(m_event.type)
    {
    case MotionNotify: //When the mouse move
        m_event.type = MouseMotionEvent;
        m_event.mouseMotion.posX = m_xEvent.xmotion.x;
        m_event.mouseMotion.posY = m_xEvent.xmotion.y;
        return;

    case ButtonPress: //When a mouse's button is pressed
        m_event.type = MouseButtonEvent;
        m_event.mouseButton.button = m_xEvent.xbutton.button;
        m_event.mouseButton.isPressed = true;
        return;

    case ButtonRelease: //When a mouse's button is released
        m_event.type = MouseButtonEvent;
        m_event.mouseButton.button = m_xEvent.xbutton.button;
        m_event.mouseButton.isPressed = false;
        return;

    case EnterNotify: //When the window enter in the window
        m_event.type = MouseFocusEvent;
        m_event.mouseFocus.isFocusIn = true;
        return;

    case LeaveNotify: //When the mouse leave of the window
        m_event.type = MouseFocusEvent;
        m_event.mouseFocus.isFocusIn = false;
        return;

    case FocusIn:
        m_event.type = KeyboardFocusEvent;
        m_event.keyboardFocus.isFocusIn = true;
        return;

    case FocusOut:
        m_event.type = KeyboardFocusEvent;
        m_event.keyboardFocus.isFocusIn = false;
        return;

    case KeyPress: //When a keyboard's key is pressed
        m_event.type = KeyEvent;
        m_event.key.isPressed = true;
        //... XLookupKeySym()
        return;

    case KeyRelease: //When a keyboard's key is released
        m_event.type = KeyEvent;
        m_event.key.isPressed = false;
        //...
        return;

    case ConfigureNotify: //When the window's position, size has changed
        if(m_xEvent.xconfigure.width != m_width ||
           m_xEvent.xconfigure.height !=m_height)
        {
            m_event.type = WindowResizeEvent;
            m_width = m_xEvent.xconfigure.width;
            m_height = m_xEvent.xconfigure.height;
            m_event.windowResize.width = m_width;
            m_event.windowResize.height = m_height;
            return;
        }
        else if(m_xEvent.xconfigure.x != m_posX ||
                m_xEvent.xconfigure.y != m_posY)
        {
            m_event.type = WindowMoveEvent;
            m_posX = m_xEvent.xconfigure.x;
            m_posY = m_xEvent.xconfigure.y;
            m_event.windowMove.posX = m_posX;
            m_event.windowMove.posY = m_posY;
            return;
        }
        return;

    case ClientMessage:
        if(m_xEvent.xclient.data.l[0] == m_destroyWindowEvent)
        {
            m_event.type = WindowDestroyEvent;
            XDestroyWindow(m_display, m_window);
            return;
        }
        return;
    }
}

}
