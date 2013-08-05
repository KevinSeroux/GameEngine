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

class WindowAttributes;

///////////////////////////////////////////////////////////////////////////////
/// \brief The implementation for X server
///
/// \todo \li Add styles
///       \li UTF-8 Title
///       \li Icon
///       \li Custom cursor
///       \li Hide the cursor
///       \li Fullscreen (See to reduce the variable with static)
///
/// \test Child window
///////////////////////////////////////////////////////////////////////////////
class XWindow : public BaseImplWindow
{
public:
    XWindow(const WindowAttributes* const attributes);
    ~XWindow();
    void destroy();
    void displayFullScreenMode(bool const isInFullScreen);
    void isVisible(bool const visibility);
    bool checkEvent();
    bool waitEvent();
    void move(uint16_t const posX, uint16_t const posY);
    void resize(uint16_t const width, uint16_t const height);

private:
    bool processEvent();

    static Display* s_display;
    static XEvent s_xEvent, s_fullScreenEvent;
    static Atom s_windowDestroyRequestEvent, s_wmStateAtom,
	       s_wmStateFullScreenAtom;

    uint8_t m_instance;
    Window m_window;
    bool m_isVisible, m_wasIconified;
};

inline void XWindow::move(uint16_t const posX, uint16_t const posY)
{
    XMoveWindow(s_display, m_window, posX, posY);
}

inline void XWindow::resize(uint16_t const width, uint16_t const height)
{
    XResizeWindow(s_display, m_window, width, height);
}

}

#endif
