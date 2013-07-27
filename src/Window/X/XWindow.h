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

#ifndef XWINDOW__H
#define XWINDOW__H

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <stdint.h>
#include "GameEngine/Window/Window.h"

namespace window
{

class XWindow : public ImplBaseWindow
{
public:
    XWindow(const char* const title, bool const isFullScreen, uint16_t posX,
            uint16_t posY, uint16_t width, uint16_t height);
    ~XWindow();
    void changeVisibility();
    const Event* const getEventStructure();
    bool getEvent();
    void waitEvent();
    void move(uint16_t const posX, uint16_t const posY);
    void resize(uint16_t const width, uint16_t const height);

private:
    Display* m_display;
    Window m_window;
    XEvent m_xEvent;
    Event m_event;
    Atom m_destroyWindowEvent;
    bool m_isVisible;
    uint16_t m_width, m_height, m_posX, m_posY;
};

inline XWindow::~XWindow()
{
    XCloseDisplay(m_display);
}

inline const Event* const XWindow::getEventStructure()
{
    return &m_event;
}

inline void XWindow::move(uint16_t const posX, uint16_t const posY)
{
    XMoveWindow(m_display, m_window, posX, posY);
}

inline void XWindow::resize(uint16_t const width, uint16_t const height)
{
    XResizeWindow(m_display, m_window, width, height);
}

}

#endif
