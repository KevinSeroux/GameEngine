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
/// \brief

#ifndef COMMON_CONFIG__H
#define COMMON_CONFIG__H

#include "GameEngine/Config.h"

#ifdef COMMON_SHARED
	#define GE_COMMON GE_IMPORT
#else
	#ifdef BUILD_COMMON_AS_SHARED
		#define GE_COMMON GE_EXPORT
	#else
		#define GE_COMMON
	#endif
#endif

#endif //COMMON_CONFIG__H