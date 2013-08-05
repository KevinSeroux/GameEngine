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
/// \brief Allow to create window without care about the system used

#ifndef WINDOW__H
#define WINDOW__H

#include "GameEngine/Common/Config.h"

#ifdef WINDOWS_SYSTEM
	#include "GameEngine/Window/Win32/WGL/WGLContext.h"
#elif defined(LINUX_SYSTEM)
	#include "GameEngine/Window/X/GLXContext.h"
#endif

//Forward declaration
typedef int16_t;

namespace window
{

#ifdef WINDOWS_SYSTEM

    ////////////////////////////////////////////////////////////////////////////
    /// \typedef
    /// \brief When you compile on Windows RenderWindow is an alias to create a
    ///        Win32 window
    ////////////////////////////////////////////////////////////////////////////
    typedef Win32Window Window;
	typedef WGLContext GLRenderWindow;

#elif defined(LINUX_SYSTEM)

    ////////////////////////////////////////////////////////////////////////////
    /// \typedef
    /// \brief When you compile on Linux RenderWindow is an alias to create a
    ///        X.org window
    ////////////////////////////////////////////////////////////////////////////
    typedef XWindow Window;
	typedef GLXContext GLRenderWindow;

#endif

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Contain all the parameters to create a window
    ////////////////////////////////////////////////////////////////////////////
    struct WindowAttributes
    {
		bool show;

        wchar_t* title;
		char* iconURL;
		bool displayCursor;
        Window* parent;
		unsigned char openGLVersion;
        bool fullScreen;
        int16_t posX;
        int16_t posY;
        int16_t width;
        int16_t height;
    };
}

#endif // WINDOW__H
