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
/// \brief This file contain the log tools
/// \todo Add an indicative time before the messages in the default loggers

#ifndef LOGGER__H
#define LOGGER__H

#include "GameEngine/Common/Config.h"
#include "GameEngine/Common/SmartPtr.h"

namespace common
{

////////////////////////////////////////////////////////////////////////////////
/// \brief This is the base class for loggers compatible with the engine Logger
///        system
////////////////////////////////////////////////////////////////////////////////
class LoggerBase
{
public:
    ////////////////////////////////////////////////////////////////////////////
    /// \brief This is the overload to log messages
    ///
    /// \details This overload works as the printf() function
    ///
    /// \param[in] message It's your message. UTF-8 is supported.
    /// \param[in] ... It's the optionals arguments
    ////////////////////////////////////////////////////////////////////////////
	virtual void operator()(const char* const message, ...) = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// \brief This is the class which contain the instance of the three types of
///        loggers or your own
////////////////////////////////////////////////////////////////////////////////
class GAME_ENGINE_EXPORT Logger
{
public:
    ////////////////////////////////////////////////////////////////////////////
    /// \brief Allow to set your own information logger
    ///
    /// \details The logger specified will be used by the engine
    ///
    /// \param[in] logger It's your logger instance
    ////////////////////////////////////////////////////////////////////////////
	static void setInfoLogger(LoggerBase* const logger);

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Allow to set your own warning logger
    ///
    /// \details The logger specified will be used by the engine
    ///
    /// \param[in] logger It's your logger instance
    ////////////////////////////////////////////////////////////////////////////
	static void setWarningLogger(LoggerBase* const logger);

    ////////////////////////////////////////////////////////////////////////////
	/// \brief Allow to set your own warning logger
	///
    /// \details The logger specified will be used by the engine
    ///
    /// \param[in] logger It's your logger instance
    ////////////////////////////////////////////////////////////////////////////
	static void setErrorLogger(LoggerBase* const logger);

    ////////////////////////////////////////////////////////////////////////////
    /// \brief This function must be called to log your information message
    ///
    /// \details The default info logger just write in console your message,
    ///          for example : \code{.cpp}
    ///          Logger::logInfo()("GL version : %s", version); \endcode
    ///          Console output : <em>GL version : 3.2</em>
    ///
	/// \return The current info logger instance
	////////////////////////////////////////////////////////////////////////////
	static LoggerBase& logInfo();

    ////////////////////////////////////////////////////////////////////////////
    /// \brief This function must be called to log your warning message
    ///
    /// \details The warning messages are used to report an action which can
    ///          cause trouble.
    ///          The default warning logger add "[WARNING]" before the message,
    ///          for example : \code{.cpp}
    ///          Logger::logWarning()("The window's width is negative"); \endcode
    ///          Console output : <em>[WARNING] The window's width is negative
    ///          </em>
    ///
	/// \return The current warning logger instance
	////////////////////////////////////////////////////////////////////////////
	static LoggerBase& logWarning();

    ////////////////////////////////////////////////////////////////////////////
    /// \brief This function must be called to log your error message
    ///
    /// \details The default error logger add "[ERROR]" before the message,
    ///          for example : \code{.cpp}
    ///          Logger::logError()("Failed to load %s", "cube.obj"); \endcode
    ///          Console output : <em>[ERROR] Failed to load cube.obj</em>
    ///
	/// \return The current error logger instance
	////////////////////////////////////////////////////////////////////////////
	static LoggerBase& logError();

private:
	Logger();

    static SmartPtr<LoggerBase> m_infoLogger;
    static SmartPtr<LoggerBase> m_warningLogger;
    static SmartPtr<LoggerBase> m_errorLogger;
};

}

#endif //LOGGER__H
