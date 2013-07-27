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

#ifndef LOGGER__H
#define LOGGER__H

#include "GameEngine/Common/Config.h"
#include "GameEngine/Common/SmartPtr.h"
#include <iostream>
#include <sstream>
#include <cstdarg>
#include <cstdio>

namespace common
{

class GAME_ENGINE_EXPORT LoggerBase
{
public:
	virtual void operator()(const char* const message, ...) = 0;

private:
	std::wostringstream m_stream;
};

struct GAME_ENGINE_EXPORT InfoLogger : public LoggerBase
{
	void operator()(const char* const message, ...);
};

struct GAME_ENGINE_EXPORT WarningLogger : public LoggerBase
{
	void operator()(const char* const message, ...);
};

struct GAME_ENGINE_EXPORT ErrorLogger : public LoggerBase
{
	void operator()(const char* const message, ...);
};

class GAME_ENGINE_EXPORT Logger
{
public:
	static void setInfoLogger(LoggerBase* const logger);
	static void setWarningLogger(LoggerBase* const logger);
	static void setErrorLogger(LoggerBase* const logger);
	static LoggerBase& logInfo();
	static LoggerBase& logWarning();
	static LoggerBase& logError();

private:
	Logger();

    static SmartPtr<LoggerBase> m_infoLogger;
    static SmartPtr<LoggerBase> m_warningLogger;
    static SmartPtr<LoggerBase> m_errorLogger;
};

}

#endif //LOGGER__H
