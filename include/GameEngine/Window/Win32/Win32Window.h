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

#ifndef WIN32_WINDOW__H
#define WIN32_WINDOW__H

#include <stdint.h>
#include <Windows.h>
#include "GameEngine/Window/BaseImplWindow.h"
#include "../Config.h"
#include "WGL/WGLContext.h"
#include <thread>

namespace window
{

//Forward declaration
class WindowAttributes;

/// \todo capture the pointer by move the pointer to the center of the window
class Win32Window : public BaseImplWindow
{
public:
	GE_WINDOW virtual ~Win32Window();
	GE_WINDOW void close();
	bool const isAlive();
	GE_WINDOW void start(WindowAttributes * const attributes);

	virtual void onEvent(Event const * const p_event) = 0;

	GE_WINDOW uint16_t const getPosX();
	GE_WINDOW uint16_t const getPosY();
	void move(uint16_t const posX, uint16_t const posY);
	GE_WINDOW uint16_t const getWidth();
	GE_WINDOW uint16_t const getHeight();
	void resize(uint16_t const width, uint16_t const height);
	void moveResize(uint16_t const posX, uint16_t const posY,
					uint16_t const width, uint16_t const height);

	void setState(char const visibility);
	GE_WINDOW void displayFullScreenMode(bool const inFullScreen);

	void displayCursor(bool const mustDisplayCursor);
	void moveCursor(uint16_t const posX, uint16_t const posY);

	void swapBuffers() const;

private:
	static LRESULT CALLBACK windowProc(HWND hwnd, UINT message, WPARAM wParam,
	                                   LPARAM lParam);
	GE_WINDOW void run(WindowAttributes * const attributes);

	bool m_inFullScreen, m_cursorCaptured;
	volatile bool m_isAlive;
	std::thread* m_inputThread;
	volatile bool m_isInputThreadReady;
	HWND m_windowHandle;
	WGLContext m_wglContext;
};

inline void Win32Window::close()
{
	m_isAlive = false;
}

inline bool const Win32Window::isAlive()
{
	return m_isAlive;
}


inline void Win32Window::move(uint16_t const posX, uint16_t const posY)
{
	MoveWindow(m_windowHandle, posX, posY, getWidth(), getHeight(), FALSE);
}

inline void Win32Window::resize(uint16_t const width, uint16_t const height)
{
	MoveWindow(m_windowHandle, getPosX(), getPosY(), width, height, FALSE);
}

inline void Win32Window::moveResize(uint16_t const posX, uint16_t const posY,
									uint16_t const width, uint16_t const height)
{
	MoveWindow(m_windowHandle, posX, posY, width, height, FALSE);
}


inline void Win32Window::setState(char const visibility)
{
    ShowWindow(m_windowHandle, visibility);
}


inline void Win32Window::displayCursor(bool const mustDisplayCursor)
{
	ShowCursor(mustDisplayCursor);
}

inline void Win32Window::moveCursor(uint16_t const posX, uint16_t const posY)
{
	SetCursorPos(posX, posY);
}


inline void Win32Window::swapBuffers() const
{
	m_wglContext.swapBuffers();
}

}

#endif // WIN32_WINDOW__H
