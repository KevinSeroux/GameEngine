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

#ifndef IMPLBASEWINDOW__H
#define IMPLBASEWINDOW__H

#include "GameEngine/Window/Event.h"

namespace window
{

/// \brief Abstract class for an implementation of a window system
class BaseImplWindow
{
public:
    ////////////////////////////////////////////////////////////////////////////
    /// \brief Get the count of existing windows
    ////////////////////////////////////////////////////////////////////////////
    static uint8_t const getCountInstance();

    BaseImplWindow();
    virtual ~BaseImplWindow();

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
    bool const exist();

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Allow to show or hide the window
    ///
    /// \details This function don't iconify/maximize the window
    ///
    /// \param[in] visibility \c true to show the window or \c false to hide
    ///
    virtual void isVisible(bool const visibility) = 0;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Return a pointer to the event structure updated by checkEvent()
    ///        or waitEvent()
    ///
    /// \details Normally, you just need to get the pointer just one time
    ////////////////////////////////////////////////////////////////////////////
    const Event* const getEventStructure();

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
    virtual bool waitEvent() = 0;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Get the abscissa position of the window
    ///
    /// \sa getPosY()
    /// \sa move()
    ////////////////////////////////////////////////////////////////////////////
    uint16_t const getPosX();

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Get the ordinate position of the window
    ///
    /// \sa getPosX()
    /// \sa move()
    ////////////////////////////////////////////////////////////////////////////
    uint16_t const getPosY();

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Move the window on the desktop
    ///
    /// \param[in] posX The new abscissa position on the desktop
    /// \param[in] posY The new ordinate position on the desktop
    ///
    /// \warning This function, when overloaded, must update m_posX and m_posY
    ///
    /// \sa resize()
    ////////////////////////////////////////////////////////////////////////////
    virtual void move(uint16_t const posX, uint16_t const posY) = 0;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Get the width of the window (in pixel)
    ///
    /// \sa getHeight()
    /// \sa resize()
    ////////////////////////////////////////////////////////////////////////////
    uint16_t const getWidth();

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Get the height of the window (in pixel)
    ///
    /// \sa getWidth()
    /// \sa resize()
    ////////////////////////////////////////////////////////////////////////////
    uint16_t const getHeight();

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Allow to resize the window
    ///
    /// \param[in] width The new width of the window
    /// \param[in] height The new height of the window
    ///
    /// \warning This function, when overloaded, must update m_width and
    ///          m_height
    ///
    /// \sa move()
    ////////////////////////////////////////////////////////////////////////////
    virtual void resize(uint16_t const width, uint16_t const height) = 0;

protected:
    ////////////////////////////////////////////////////////////////////////////
    /// \brief The count of existing windows
    ////////////////////////////////////////////////////////////////////////////
    static uint8_t m_countInstance;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief The instance number of the window
    ////////////////////////////////////////////////////////////////////////////
    uint8_t m_instance;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief The events structure of the instance
    ////////////////////////////////////////////////////////////////////////////
    Event m_event;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief The abscissa position of the window
    ////////////////////////////////////////////////////////////////////////////
    uint16_t m_posX;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief The ordinate position of the window
    ////////////////////////////////////////////////////////////////////////////
    uint16_t m_posY;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief The width of the window
    ////////////////////////////////////////////////////////////////////////////
    uint16_t m_width;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief The height of the window
    ////////////////////////////////////////////////////////////////////////////
    uint16_t m_height;
};

inline uint8_t const BaseImplWindow::getCountInstance()
{
    return m_countInstance;
}

inline const Event* const BaseImplWindow::getEventStructure()
{
    return &m_event;
}

inline uint16_t const BaseImplWindow::getPosX()
{
    return m_posX;
}

inline uint16_t const BaseImplWindow::getPosY()
{
    return m_posY;
}

inline uint16_t const BaseImplWindow::getWidth()
{
    return m_width;
}

inline uint16_t const BaseImplWindow::getHeight()
{
    return m_height;
}

}

#endif // IMPLBASEWINDOW__H
