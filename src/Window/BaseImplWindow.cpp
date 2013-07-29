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

#include "GameEngine/Window/BaseImplWindow.h"

namespace window
{

uint8_t BaseImplWindow::m_countInstance = 0;

BaseImplWindow::BaseImplWindow()
{
    m_countInstance++;
    m_instance = m_countInstance;
}

BaseImplWindow::~BaseImplWindow() {}

bool const BaseImplWindow::exist()
{
    if(m_instance != 0)
        return true;
    else
        return false;
}

}

