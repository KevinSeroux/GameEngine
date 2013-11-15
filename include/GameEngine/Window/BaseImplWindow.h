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
/// \brief Provide a base implementation of a window

#ifndef BASEIMPLWINDOW__H
#define BASEIMPLWINDOW__H

#include <stdint.h>
#include "Config.h"

namespace window
{
	
//Forward declaration
class Event;

/// \brief Abstract class for an implementation of a window system
class BaseImplWindow
{
public:
    ////////////////////////////////////////////////////////////////////////////
    /// \brief Return a pointer to the event structure updated by checkEvent()
    ///        or waitEvent()
    ///
    /// \details Normally, you just need to get the pointer just one time
    ////////////////////////////////////////////////////////////////////////////
    static const Event* const getEventStructure();

	////////////////////////////////////////////////////////////////////////////

	GE_WINDOW virtual ~BaseImplWindow();

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Destroy the window.
    ////////////////////////////////////////////////////////////////////////////
    virtual void destroy() = 0;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Allow to know is the window exist
    ///
    /// \return \c true if the window exist, \c false is the window has been
    ///         destroyed
    ////////////////////////////////////////////////////////////////////////////
    virtual bool const isAlive() = 0;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Detect if an event is occured
    ///
    /// \return \c true if an event is occured on the window, else false
    ///
    /// \sa waitEvent()
    ////////////////////////////////////////////////////////////////////////////
    virtual bool checkEvent() = 0;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Block the program until an event occur
    ///
    /// \return \c true if the event is treatable, else \c false
    ///
    /// \sa checkEvent()
    ////////////////////////////////////////////////////////////////////////////
    virtual void waitEvent() = 0;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Get the horizontal position of the window
    ///
    /// \sa getPosY()
    /// \sa move()
    ////////////////////////////////////////////////////////////////////////////
    virtual uint16_t const getPosX() = 0;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Get the vertical position of the window
    ///
    /// \sa getPosX()
    /// \sa move()
    ////////////////////////////////////////////////////////////////////////////
    virtual uint16_t const getPosY() = 0;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Move the window on the desktop
    ///
    /// \param[in] posX The new horizontal position on the desktop
    /// \param[in] posY The new vertical position on the desktop
    ///
    /// \sa resize()
	/// \sa moveResize()
    ////////////////////////////////////////////////////////////////////////////
    virtual void move(uint16_t const posX, uint16_t const posY) = 0;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Get the width of the window (in pixel)
    ///
    /// \sa getHeight()
    /// \sa resize()
    ////////////////////////////////////////////////////////////////////////////
    virtual uint16_t const getWidth() = 0;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Get the height of the window (in pixel)
    ///
    /// \sa getWidth()
    /// \sa resize()
    ////////////////////////////////////////////////////////////////////////////
    virtual uint16_t const getHeight() = 0;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Allow to resize the window
    ///
    /// \param[in] width The new width of the window
    /// \param[in] height The new height of the window
    ///
    /// \sa move()
	/// \sa moveResize()
    ////////////////////////////////////////////////////////////////////////////
    virtual void resize(uint16_t const width, uint16_t const height) = 0;
	
    ////////////////////////////////////////////////////////////////////////////
	/// \Allow to move and resize the window
	///
	/// \param[in] posX The new horizontal position on the desktop
	/// \param[in] posY The new vertical position on the desktop
	/// \param[in] width The new width of the window
	/// \param[in] height The new height of the window
	///
	/// \sa move()
	/// \sa resize()
    ////////////////////////////////////////////////////////////////////////////
	virtual void moveResize(uint16_t const posX, uint16_t const posY,
							uint16_t const width, uint16_t const height) = 0;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Allow to show or hide the window
    ///
    /// \details This function don't iconify/maximize the window
    ///
    /// \param[in] visibility \c true to show the window or \c false to hide
    ///
    virtual void setState(char const visibility) = 0;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Enable or disable the fullscreen mode
	///
	/// \param[in] inFullScreen \c true to switch in fullscreen mode and \c
	///            false to go back in windowed mode
    ////////////////////////////////////////////////////////////////////////////
    virtual void displayFullScreenMode(bool const inFullScreen) = 0;

	////////////////////////////////////////////////////////////////////////////
	/// \brief Show or hide the cursor
	///
	/// \details Useful for example to use your own cursor with a 3D UI
	///
	/// \param[in] isCursorDisplayed \c true to display the cursor and \c false
	///            to hide it
	////////////////////////////////////////////////////////////////////////////
	virtual void displayCursor(bool const isCursorDisplayed) = 0;

	////////////////////////////////////////////////////////////////////////////
	/// \brief Move the cursor to the specified location
	///
	/// \param[in] posX The horizontal position of the cursor
	/// \param[in] posY The vertical position of the cursor
	////////////////////////////////////////////////////////////////////////////
	virtual void moveCursor(uint16_t const posX, uint16_t const posY) = 0;

protected:
    GE_WINDOW static Event s_event;
};

inline const Event* const BaseImplWindow::getEventStructure()
{
	return &s_event;
}

}

#endif // BASEIMPLWINDOW__H
