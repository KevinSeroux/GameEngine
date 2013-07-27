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

#ifndef WINDOW__H
#define WINDOW__H

#include <stdint.h>
#include "GameEngine/Common/Config.h"

namespace window
{

namespace event
{

#define KeyEvent 0
struct Key
{
    bool isPressed;
    uint16_t keycode;
};

#define MouseMotionEvent 1
struct MouseMotion
{
    uint16_t posX, posY;
};

#define MouseButtonEvent 2
struct MouseButton
{
    bool isPressed;
    uint8_t button;
};

#define MouseFocusEvent 3
struct MouseFocus
{
    bool isFocusIn;
};

#define KeyboardFocusEvent 4
struct KeyboardFocus
{
    bool isFocusIn;
};

#define WindowMoveEvent 5
struct WindowMove
{
    uint16_t posX, posY;
};

#define WindowResizeEvent 6
struct WindowResize
{
    uint16_t width, height;
};

#define WindowHidden     0
#define WindowObstructed 1
#define WindowVisible    2

#define WindowVisibilityEvent 7
struct WindowVisibility
{
    char state;
};

#define WindowDestroyEvent 8

}

struct GAME_ENGINE_EXPORT Event
{
    uint8_t type;
    event::Key key;
    event::MouseMotion mouseMotion;
    event::MouseButton mouseButton;
    event::MouseFocus mouseFocus;
    event::KeyboardFocus keyboardFocus;
    event::WindowMove windowMove;
    event::WindowVisibility windowVisibility;
    event::WindowResize windowResize;
};

class ImplBaseWindow
{
public:
    virtual ~ImplBaseWindow() {};
    virtual void changeVisibility() = 0;
    virtual const Event* const getEventStructure() = 0;
    virtual bool getEvent() = 0;
    virtual void waitEvent() = 0;
    virtual void move(uint16_t const posX, uint16_t const posY) = 0;
    virtual void resize(uint16_t const width, uint16_t const height) = 0;
};

typedef ImplBaseWindow RenderWindow;

/// \brief Think to delete the returned instance !!!
RenderWindow* const createWindow(const char* const title,
                                 bool const isFullScreen, uint16_t posX,
                                 uint16_t posY, uint16_t width,
                                 uint16_t height);

}

#endif // WINDOW__H
