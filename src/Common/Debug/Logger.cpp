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

#include <cstdio>
#include <cstdarg>
#include <iostream>
#include "GameEngine/Common/Debug/Logger.h"

namespace common
{

struct InfoLogger : public LoggerBase
{
	void operator()(const char* const message, ...)
	{
	    va_list pa;
        va_start(pa, message);
        vprintf(message, pa);
        std::cout << std::endl;
        va_end(pa);
    }
};

struct WarningLogger : public LoggerBase
{
	void operator()(const char* const message, ...)
	{
        va_list pa;
        va_start(pa, message);
        printf("[WARNING] ");
        vprintf(message, pa);
        std::cout << std::endl;
        va_end(pa);
	}
};

struct ErrorLogger : public LoggerBase
{
	void operator()(const char* const message, ...)
	{
        va_list pa;
        va_start(pa, message);
        printf("[ERROR] ");
        vprintf(message, pa);
        std::cout << std::endl;
        va_end(pa);
	}
};

SmartPtr<LoggerBase> Logger::m_infoLogger;
SmartPtr<LoggerBase> Logger::m_warningLogger;
SmartPtr<LoggerBase> Logger::m_errorLogger;

GAME_ENGINE_EXPORT void Logger::setInfoLogger(LoggerBase* const logger)
{
    m_infoLogger = logger;
}

GAME_ENGINE_EXPORT void Logger::setWarningLogger(LoggerBase* const logger)
{
    m_warningLogger = logger;
}

GAME_ENGINE_EXPORT void Logger::setErrorLogger(LoggerBase* const logger)
{
    m_errorLogger = logger;
}

GAME_ENGINE_EXPORT LoggerBase& Logger::logInfo()
{
    if(m_infoLogger == 0)
        m_infoLogger = new InfoLogger;
    return *m_infoLogger;
}

GAME_ENGINE_EXPORT LoggerBase& Logger::logWarning()
{
    if(m_warningLogger == 0)
        m_warningLogger = new WarningLogger;
    return *m_warningLogger;
}

GAME_ENGINE_EXPORT LoggerBase& Logger::logError()
{
    if(m_errorLogger == 0)
        m_errorLogger = new ErrorLogger;
    return *m_errorLogger;
}

}
