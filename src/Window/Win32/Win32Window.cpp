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

#include "GameEngine/Window/Win32/Win32Window.h"
#include "GameEngine/Window/Window.h"
#include "GameEngine/Window/Event.h"
#include "GameEngine/Common/Debug/Logger.h"

#include <iostream>

using namespace common;

namespace window
{

TRACKMOUSEEVENT Win32Window::s_mouseLeaveEvent;

LRESULT CALLBACK Win32Window::windowProc(HWND hwnd, UINT message, WPARAM wParam,
										 LPARAM lParam)
{
	switch(message)
	{
	default:
		s_event.type = 0;
		return DefWindowProc(hwnd, message, wParam, lParam);

	/////////////////////////////// MOUSE MESSAGE //////////////////////////////

	/*case WM_LBUTTONDOWN:
		s_event.type = MouseButtonEvent;
		s_event.events.mouseButton.isPressed = true;
		s_event.events.mouseButton.button = 1;
		return 0;

	case WM_LBUTTONUP:
		s_event.type = MouseButtonEvent;
		s_event.events.mouseButton.isPressed = false;
		s_event.events.mouseButton.button = 1;
		return 0;

	case WM_MBUTTONDOWN:
		s_event.type = MouseButtonEvent;
		s_event.events.mouseButton.isPressed = true;
		s_event.events.mouseButton.button = 2;
		return 0;

	case WM_MBUTTONUP:
		s_event.type = MouseButtonEvent;
		s_event.events.mouseButton.isPressed = false;
		s_event.events.mouseButton.button = 2;
		return 0;

	case WM_RBUTTONDOWN:
		s_event.type = MouseButtonEvent;
		s_event.events.mouseButton.isPressed = true;
		s_event.events.mouseButton.button = 3;
		return 0;

	case WM_RBUTTONUP:
		s_event.type = MouseButtonEvent;
		s_event.events.mouseButton.isPressed = false;
		s_event.events.mouseButton.button = 3;
		return 0;

	case WM_MOUSEWHEEL:
		s_event.type = MouseButtonEvent;
		s_event.events.mouseButton.isPressed = false;

		if(HIWORD(wParam) > 0)
			s_event.events.mouseButton.button = 4;
		else
			s_event.events.mouseButton.button = 5;

		return 0;

	case WM_MOUSEHWHEEL:
		s_event.type = MouseButtonEvent;
		s_event.events.mouseButton.isPressed = false;

		if(HIWORD(wParam) < 0)
			s_event.events.mouseButton.button = 6;
		else
			s_event.events.mouseButton.button = 7;
			
		return 0;

	case WM_MOUSELEAVE:
		s_event.type = MouseLeaveEvent;
		return 0;*/

	case WM_MOUSEMOVE:
		s_event.type = MouseMotionEvent;
		s_event.events.mouseMotion.posX = LOWORD(lParam);
		s_event.events.mouseMotion.posY = HIWORD(lParam);

		s_mouseLeaveEvent.hwndTrack = hwnd;
		TrackMouseEvent(&s_mouseLeaveEvent);

		return 0;

	/////////////////////////////// FOCUS MESSAGE //////////////////////////////

	case WM_SETFOCUS:
		s_event.type = FocusInWindowEvent;
		Logger::logInfo()("WM_SETFOCUS");
		return 0;

	case WM_KILLFOCUS:
		s_event.type = FocusOutWindowEvent;
		Logger::logInfo()("WM_KILLFOCUS");
		return 0;

	////////////////////////////// WINDOW MESSAGE //////////////////////////////

	/*case WM_MOVING:
		s_event.type = WindowMoveEvent;
		s_event.events.windowMove.posX = LOWORD(lParam);
		s_event.events.windowMove.posY = HIWORD(lParam);
		return TRUE;

	case WM_SIZING:
		{
			RECT* rect = reinterpret_cast<RECT*>(lParam);
			s_event.type = 0;
			s_event.events.windowResize.width = rect->right - rect->left;
			s_event.events.windowResize.height = rect->bottom - rect->top;
			return TRUE;
		}

	case WM_SIZE:
		switch(wParam)
		{
		/*case SIZE_RESTORED:
			s_event.type = WindowResizeEvent;
			s_event.events.windowResize.width = LOWORD(lParam);
			s_event.events.windowResize.height = HIWORD(lParam);
			break;

		case SIZE_MAXIMIZED:
			s_event.type = WindowResizeEvent;
			s_event.events.windowResize.width = LOWORD(lParam);
			s_event.events.windowResize.height = HIWORD(lParam);
			break;

		case SIZE_MINIMIZED:
			s_event.type = WindowHiddenEvent;
			Logger::logInfo()("SIZE_MINIMIZED");
			break;

		default:
			s_event.type = 0;
			break;
		}
		return 0;

	case WM_CLOSE:
		s_event.type = WindowDestroyRequestEvent;
		return 0;*/
	}
}

// Thanks to Bob Moore for the tip http://bobmoore.mvps.org/Win32/w32tip72.htm
void Win32Window::getVisibility(HWND hwnd)
{
	static char prevState;

	HDC hdc = GetDC(hwnd);
	RECT drawableArea;

	switch(GetClipBox(hdc, &drawableArea))
	{
	/*case NULLREGION:
		if(prevState != WindowHiddenEvent)
		{
			s_event.type = WindowHiddenEvent;
			Logger::logInfo()("NULLREGION");
			prevState = s_event.type;
		}
		else
			s_event.type = 0;
		break;*/

	case SIMPLEREGION:
		RECT fullArea;
		GetClientRect(hwnd, &fullArea);

		if(EqualRect(&drawableArea, &fullArea))
		{
			if(prevState != WindowFullyVisibleEvent)
			{
				s_event.type = WindowFullyVisibleEvent;
				prevState = s_event.type;
			}
			else
				s_event.type = 0;
		}
		break;

	default:
		s_event.type = 0;
		break;
	}

	ReleaseDC(hwnd, hdc);
}

////////////////////////////////////////////////////////////////////////////////

Win32Window::Win32Window(const WindowAttributes* const attributes)
{
	static bool isFirstInitialization = true;
	static HINSTANCE hInstance = GetModuleHandle(0);
	static WNDCLASS wc;

	m_isAlive = true;
	m_inFullScreen = attributes->fullScreen;

	//To receive WM_MOUSELEAVE
	if(isFirstInitialization == true)
	{
		wc.style = CS_OWNDC; //For OGL context
		wc.lpfnWndProc = windowProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;

		wc.hIcon = NULL;
		wc.hCursor = NULL;

		wc.lpszMenuName = NULL;
		wc.lpszClassName = "0";

		s_mouseLeaveEvent.cbSize = sizeof(TRACKMOUSEEVENT);
		s_mouseLeaveEvent.dwFlags = TME_LEAVE;
		isFirstInitialization = false;
	}

	////////////////////////////// ICON MANAGEMENT /////////////////////////////
	HICON icon = reinterpret_cast<HICON>
		(LoadImage(hInstance, attributes->iconURL, IMAGE_ICON, 0, 0,
		LR_DEFAULTSIZE | LR_LOADFROMFILE | LR_SHARED));

	if(icon == NULL)
		Logger::logWarning()("Failed to load the following icon : %s",
		                   attributes->iconURL);
	else
		wc.hIcon = icon;
	//////////////////////////// END ICON MANAGEMENT ///////////////////////////

    RegisterClass(&wc);

	/////////////////////////// FULLSCREEN MANAGEMENT //////////////////////////
	long style;
	uint16_t posX, posY, width, height;

	if(m_inFullScreen == true)
	{
		style = WS_POPUP | WS_MAXIMIZE;
		posX = posY = 0; /* In fullscreen mode, we don't care of the
		                        window's size */
	}
	else
	{
		style = WS_OVERLAPPEDWINDOW;

		if(attributes->posX < 0)
			posX = CW_USEDEFAULT;
		else
			posX = attributes->posX;

		if(attributes->posY < 0)
			posY = CW_USEDEFAULT;
		else
			posY = attributes->posY;

		if(attributes->width < 0)
			width = CW_USEDEFAULT;
		else
			width = attributes->width;

		if(attributes->height < 0)
			height = CW_USEDEFAULT;
		else
			height = attributes->height;
	}
	///////////////////////// END FULLSCREEN MANAGEMENT ////////////////////////

	if(attributes->show == true)
		style |= WS_VISIBLE;

	HWND parent;
	if(attributes->parent == 0)
		parent = 0;
	else
		parent = attributes->parent->m_windowHandle;

	if(attributes->displayCursor == false)
		ShowCursor(false);

	// Creation of the window
	m_windowHandle = CreateWindowW(L"0", attributes->title, style,
	                              posX, posY, width, height,
								  parent, 0, hInstance, 0);
}

Win32Window::~Win32Window()
{
	destroy();
}

void Win32Window::destroy()
{
	DestroyWindow(m_windowHandle);
	m_isAlive = false;
}


bool Win32Window::checkEvent()
{
	/*getVisibility(m_windowHandle);
	if(s_event.type != 0)
		return true;*/
	
	static MSG message;
	if(PeekMessage(&message, m_windowHandle, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
		if(s_event.type != 0)
			return true;
	}
	return false;
}

void Win32Window::waitEvent()
{
	while(WaitMessage() && checkEvent());
}


uint16_t const Win32Window::getWidth()
{
	RECT rect;
	GetWindowRect(m_windowHandle, &rect);
	return rect.right - rect.left;
}

uint16_t const Win32Window::getHeight()
{
	RECT rect;
	GetWindowRect(m_windowHandle, &rect);
	return rect.bottom - rect.top;
}

uint16_t const Win32Window::getPosX()
{
	RECT rect;
	GetWindowRect(m_windowHandle, &rect);
	return rect.left;
}

uint16_t const Win32Window::getPosY()
{
	RECT rect;
	GetWindowRect(m_windowHandle, &rect);
	return rect.top;
}


void Win32Window::displayFullScreenMode(bool const inFullScreen)
{
	if(m_inFullScreen == false)
		SetWindowLongPtr(m_windowHandle, GWL_STYLE, WS_POPUP | WS_MAXIMIZE);
	else
		SetWindowLongPtr(m_windowHandle, GWL_STYLE, WS_OVERLAPPEDWINDOW);

	m_inFullScreen = !inFullScreen;
}

} //namespace window