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
/// \brief Contains the events macros and structures

#ifndef EVENT__H
#define EVENT__H

#include "GameEngine/Common/Config.h"

namespace window
{

////////////////////////////////////////////////////////////////////////////////
/// \brief Contains all the types of event which can happen
////////////////////////////////////////////////////////////////////////////////
namespace event
{

////////////////////////////////////////////////////////////////////////////////
/// \brief The event value of KeyDown
////////////////////////////////////////////////////////////////////////////////
#define KeyDownEvent 1

////////////////////////////////////////////////////////////////////////////////
/// \brief The event when a key of the keyboard is pressed
/// \todo Find a way to manage key
////////////////////////////////////////////////////////////////////////////////
struct GAME_ENGINE_IMPORT KeyDown
{
    char* key;
};

////////////////////////////////////////////////////////////////////////////////
/// \brief The event value of KeyUp
////////////////////////////////////////////////////////////////////////////////
#define KeyUpEvent 2

////////////////////////////////////////////////////////////////////////////////
/// \brief The event when a key of the keyboard is released
/// \todo Find a way to manage key
////////////////////////////////////////////////////////////////////////////////
struct GAME_ENGINE_IMPORT KeyUp
{
    char* key;
};

////////////////////////////////////////////////////////////////////////////////
/// \brief The event value of MouseMotion
////////////////////////////////////////////////////////////////////////////////
#define MouseMotionEvent 3

////////////////////////////////////////////////////////////////////////////////
/// \brief The event when the mouse move
////////////////////////////////////////////////////////////////////////////////
struct GAME_ENGINE_IMPORT MouseMotion //4B
{
    ////////////////////////////////////////////////////////////////////////////
    /// \brief The abscissa position of the mouse
    ////////////////////////////////////////////////////////////////////////////
    uint16_t posX;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief The ordinate position of the mouse
    ////////////////////////////////////////////////////////////////////////////
    uint16_t posY;
};

////////////////////////////////////////////////////////////////////////////////
/// \brief The event value of MouseButton
////////////////////////////////////////////////////////////////////////////////
#define MouseButtonEvent 4

////////////////////////////////////////////////////////////////////////////////
/// \brief The event when a button of the mouse is pressed or released
////////////////////////////////////////////////////////////////////////////////
struct GAME_ENGINE_IMPORT MouseButton //3B
{
    ////////////////////////////////////////////////////////////////////////////
    /// \brief Have the value \c true if the button is pressed and the value
    ///        \c false if the button is released
    ////////////////////////////////////////////////////////////////////////////
    bool isPressed;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief The button which has been pressed/released
    ///
    /// \details The following values can change between mouses :
    ///
    /// \li button = 1 : Left click
    /// \li button = 2 : Middle button (wheel button)
    /// \li button = 3 : Right click
    /// \li button = 4 : Mouse wheel up (yes, it's a button !)
    /// \li button = 5 : Mouse wheel down (it's also a button)
    /// \li button = 6 : Left click on wheel
    /// \li button = 7 : Right click on wheel
    ////////////////////////////////////////////////////////////////////////////
    uint8_t button;
};

////////////////////////////////////////////////////////////////////////////////
/// \brief The event when the mouse leave the window
////////////////////////////////////////////////////////////////////////////////
#define MouseLeaveEvent 5

////////////////////////////////////////////////////////////////////////////////
/// \brief The event when the window become active
////////////////////////////////////////////////////////////////////////////////
#define FocusInWindowEvent 6

////////////////////////////////////////////////////////////////////////////////
/// \brief The event when the window become inactive, when the user has selected
///        another window
////////////////////////////////////////////////////////////////////////////////
#define FocusOutWindowEvent 7

////////////////////////////////////////////////////////////////////////////////
/// \brief The event value of WindowMove
////////////////////////////////////////////////////////////////////////////////
#define WindowMoveEvent 8

////////////////////////////////////////////////////////////////////////////////
/// \brief The event when the window move
////////////////////////////////////////////////////////////////////////////////
struct GAME_ENGINE_IMPORT WindowMove //4B
{
    ////////////////////////////////////////////////////////////////////////////
    /// \brief The new abscissa position on the desktop
    ////////////////////////////////////////////////////////////////////////////
    uint16_t posX;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief The new ordinate position on the desktop
    ////////////////////////////////////////////////////////////////////////////
    uint16_t posY;
};

////////////////////////////////////////////////////////////////////////////////
/// \brief The event value of WindowResize
////////////////////////////////////////////////////////////////////////////////
#define WindowResizeEvent 9

////////////////////////////////////////////////////////////////////////////////
/// \brief The event when the window is resized
////////////////////////////////////////////////////////////////////////////////
struct GAME_ENGINE_IMPORT WindowResize //4B
{
    ////////////////////////////////////////////////////////////////////////////
    /// \brief The new width of the window
    ////////////////////////////////////////////////////////////////////////////
    uint16_t width;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief The new height of the window
    ////////////////////////////////////////////////////////////////////////////
    uint16_t height;
};

////////////////////////////////////////////////////////////////////////////////
/// \brief The event when the window is fully hidden
////////////////////////////////////////////////////////////////////////////////
#define WindowHiddenEvent 10

////////////////////////////////////////////////////////////////////////////////
/// \brief The event when the window is fully visible
////////////////////////////////////////////////////////////////////////////////
#define WindowFullyVisibleEvent 11

////////////////////////////////////////////////////////////////////////////////
/// \brief The event value when the user click on the close button of the window
////////////////////////////////////////////////////////////////////////////////
#define WindowDestroyRequestEvent 12

}

////////////////////////////////////////////////////////////////////////////////
/// \brief List of events
////////////////////////////////////////////////////////////////////////////////
union GAME_ENGINE_IMPORT EventList
{
	event::KeyDown keyDown;
    event::KeyUp keyUp;
    event::MouseMotion mouseMotion;
    event::MouseButton mouseButton;
    event::WindowMove windowMove;
    event::WindowResize windowResize;
};

////////////////////////////////////////////////////////////////////////////////
/// \brief The main structure event the user will manipulate
////////////////////////////////////////////////////////////////////////////////
struct GAME_ENGINE_IMPORT Event
{
    ////////////////////////////////////////////////////////////////////////////
    /// \brief Correspond of one of the event value. Do not confusing with the
    ///        visibility state value
    ////////////////////////////////////////////////////////////////////////////
    uint8_t type;

    EventList events;
};

}

#endif // EVENT__H
