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

/// \file
/// \brief Contain the XWindow implementation

#ifndef XWINDOW__H
#define XWINDOW__H

#include <X11/Xlib.h>
#include "GameEngine/Window/BaseImplWindow.h"
#include "GameEngine/Window/Event.h"

namespace window
{

///////////////////////////////////////////////////////////////////////////////
/// \brief The implementation for X server
///
/// \todo \li Add styles
///       \li UTF-8 Title
///       \li Icon
///       \li Custom cursor
///       \li Hide the cursor
///////////////////////////////////////////////////////////////////////////////
class XWindow : public BaseImplWindow
{
public:
    XWindow(const char* const title, bool const isFullScreen,
            uint16_t const posX, uint16_t const posY,
            uint16_t const width, uint16_t const height);
    ~XWindow();
    void destroy();
    void isVisible(bool const visibility);
    bool checkEvent();
    bool waitEvent();
    void move(uint16_t const posX, uint16_t const posY);
    void resize(uint16_t const width, uint16_t const height);

private:
    bool processEvent();

    static Display* m_display;
    static XEvent m_xEvent;
    static Atom m_windowDestroyRequestEvent;

    uint8_t m_instance;
    Window m_window;
    bool m_isVisible;
};

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
