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

#include "GameEngine/Window/Window.h"

#ifdef WINDOWS_SYSTEM
    #include "Win32/Win32Window.h"
    typedef window::Win32Window WindowImpl;
#elif defined(LINUX_SYSTEM)
    #include "X/XWindow.h"
    typedef window::XWindow WindowImpl;
#endif

namespace window
{

RenderWindow* const createWindow(const char* const title,
                                 bool const isFullScreen, uint16_t posX,
                                 uint16_t posY, uint16_t width,
                                 uint16_t height)
{
    return new WindowImpl(title, isFullScreen, posX, posY, width, height);
}

}
