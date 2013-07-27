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


#ifndef CONFIG__H
#define CONFIG__H

#ifdef _WIN32
    #define WINDOWS_SYSTEM
#elif defined(linux)
    #define LINUX_SYSTEM
#else
    #error Your platform is not supported
#endif

#ifndef NDEBUG
    #define DEBUG
#elif defined(_DEBUG)
    #define DEBUG
#endif

#ifdef WINDOWS_SYSTEM
    #ifdef BUILD_AS_SHARED
        #define GAME_ENGINE_EXPORT __declspec(dllexport)
        #define GAME_ENGINE_IMPORT __declspec(dllimport)
    #else
        #define GAME_ENGINE_EXPORT
        #define GAME_ENGINE_IMPORT
    #endif
#else
    #define GAME_ENGINE_EXPORT
    #define GAME_ENGINE_IMPORT
#endif

#endif //CONFIG__H
