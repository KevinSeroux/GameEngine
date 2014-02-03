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

using namespace common;

namespace window
{

LRESULT CALLBACK Win32Window::windowProc(HWND hwnd, UINT message, WPARAM wParam,
										 LPARAM lParam)
{
	switch(message)
	{
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);

	case WM_CREATE:
		{
			LONG_PTR window = (LONG_PTR)reinterpret_cast<CREATESTRUCT*>(lParam)
				->lpCreateParams;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, window);
			return 0;
		}

	///////////////////////////// KEYBOARD MESSAGE /////////////////////////////

	case WM_KEYUP:
		Logger::logInfo()("WM_KEYUP : %i", wParam);
		return 0;

	case WM_KEYDOWN:
		//Logger::logInfo()("WM_KEYDOWN : %i", wParam);
		s_event.type = event::KeyTextEvent;
		s_event.events.keyText.character = MapVirtualKey(wParam, MAPVK_VK_TO_CHAR);
		return 0;

	case WM_CHAR:
		s_event.type = event::KeyTextEvent;
		s_event.events.keyText.character = wParam;
		break;

	/////////////////////////////// MOUSE MESSAGE //////////////////////////////

	case WM_LBUTTONDOWN:
		s_event.type = event::MouseButtonEvent;
		s_event.events.mouseButton.isPressed = true;
		s_event.events.mouseButton.button = 1;
		break;

	case WM_LBUTTONUP:
		s_event.type = event::MouseButtonEvent;
		s_event.events.mouseButton.isPressed = false;
		s_event.events.mouseButton.button = 1;
		break;
		
	case WM_MBUTTONDOWN:
		s_event.type = event::MouseButtonEvent;
		s_event.events.mouseButton.isPressed = true;
		s_event.events.mouseButton.button = 2;
		break;

	case WM_MBUTTONUP:
		s_event.type = event::MouseButtonEvent;
		s_event.events.mouseButton.isPressed = false;
		s_event.events.mouseButton.button = 2;
		break;

	case WM_RBUTTONDOWN:
		s_event.type = event::MouseButtonEvent;
		s_event.events.mouseButton.isPressed = true;
		s_event.events.mouseButton.button = 3;
		break;

	case WM_RBUTTONUP:
		s_event.type = event::MouseButtonEvent;
		s_event.events.mouseButton.isPressed = false;
		s_event.events.mouseButton.button = 3;
		break;

	case WM_MOUSEWHEEL:
		s_event.type = event::MouseButtonEvent;
		s_event.events.mouseButton.isPressed = false;

		if(GET_WHEEL_DELTA_WPARAM(wParam) < 0)
			s_event.events.mouseButton.button = 5;
		else
			s_event.events.mouseButton.button = 4;

		break;

	case WM_MOUSEHWHEEL:
		s_event.type = event::MouseButtonEvent;
		s_event.events.mouseButton.isPressed = false;

		if(GET_WHEEL_DELTA_WPARAM(wParam) < 0)
			s_event.events.mouseButton.button = 6;
		else
			s_event.events.mouseButton.button = 7;

		break;

	case WM_XBUTTONDOWN:
		s_event.type = event::MouseButtonEvent;
		s_event.events.mouseButton.isPressed = true;
		if(HIWORD(wParam) == XBUTTON1)
			s_event.events.mouseButton.button = 8;
		else
			s_event.events.mouseButton.button = 9;
		break;

	case WM_XBUTTONUP:
		s_event.type = event::MouseButtonEvent;
		s_event.events.mouseButton.isPressed = false;
		if(HIWORD(wParam) == XBUTTON1)
			s_event.events.mouseButton.button = 8;
		else
			s_event.events.mouseButton.button = 9;
		break;

	case WM_MOUSELEAVE:
		s_event.type = event::MouseLeaveEvent;
		break;

	case WM_MOUSEMOVE:
		s_event.type = event::MouseMotionEvent;
		s_event.events.mouseMotion.posX = LOWORD(lParam);
		s_event.events.mouseMotion.posY = HIWORD(lParam);
		break;

	/////////////////////////////// FOCUS MESSAGE //////////////////////////////

	case WM_SETFOCUS:
		s_event.type = event::FocusInWindowEvent;
		break;

	case WM_KILLFOCUS:
		s_event.type = event::FocusOutWindowEvent;
		break;

	////////////////////////////// WINDOW MESSAGE //////////////////////////////

	case WM_MOVE:
		{
			uint16_t posX = LOWORD(lParam);
			uint16_t posY = HIWORD(lParam);

			if(posX == 33536 && posY == 33536)
				return 0;

			s_event.type = event::WindowMoveEvent;
			s_event.events.windowMove.posX = posX;
			s_event.events.windowMove.posY = posY;

			break;
		}

	case WM_SIZE:
		s_event.type = event::WindowResizeEvent;
		switch(wParam)
		{
		case SIZE_MAXIMIZED:
			s_event.type = event::WindowMaximizedEvent;
			break;

		case SIZE_MINIMIZED:
			s_event.type = event::WindowMinimizedEvent;
			break;

		default:
			s_event.type = event::WindowResizeEvent;
			s_event.events.windowResize.width = LOWORD(lParam);
			s_event.events.windowResize.height = HIWORD(lParam);
			break;
		}
		break;

	case WM_CLOSE:
		s_event.type = event::WindowDestroyRequestEvent;
		Logger::logInfo()("Request to destroy the window");
		break;
	}

	Win32Window* window = reinterpret_cast<Win32Window*>
		(GetWindowLongPtr(hwnd, GWLP_USERDATA));

	if(window->isAlive() == true)
		window->onEvent(&s_event);

	return 0;
}

////////////////////////////////////////////////////////////////////////////////

Win32Window::~Win32Window()
{
	if(m_isAlive == true)
		close();

	Logger::logInfo()("Waiting the input thread to be terminate...");
	m_inputThread->join();
	Logger::logInfo()("...Input thread terminate");
	delete m_inputThread;
}

void Win32Window::start(WindowAttributes * const attributes)
{
	m_isInputThreadReady = false;
	m_inputThread = new std::thread(&Win32Window::run, this, attributes);
	Logger::logInfo()("Input thread is creating. Waiting...");

	//We wait until the context is created
	//Replace by a message to sleep the main thread ?
	while(m_isInputThreadReady == false);
	Logger::logInfo()("...Input thread create");
	m_wglContext.enable();
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


void Win32Window::run(WindowAttributes * const attributes)
{
	static bool isFirstInitialization = true;
	static HINSTANCE hInstance = GetModuleHandle(0);
	static WNDCLASS wc;

	m_isAlive = true;
	m_inFullScreen = attributes->fullScreen;

	if(isFirstInitialization == true)
	{
		wc.style = CS_OWNDC; //For OGL context
		wc.lpfnWndProc = windowProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = sizeof(LONG_PTR); //To call specified callback function
		wc.hInstance = hInstance;

		wc.hIcon = NULL;
		wc.hCursor = NULL;

		wc.lpszMenuName = NULL;
		wc.lpszClassName = "0";

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

	////////////////////////////////////////////////////////////////////////////

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
	m_windowHandle = CreateWindow("0", attributes->title, style,
	                              posX, posY, width, height,
								  parent, 0, hInstance, this);

	m_wglContext.init(attributes, m_windowHandle);

	//Now, the context can be binded to another thread
	m_isInputThreadReady = true;

	MSG msg;
	while(m_isAlive == true)
	{
		//Use filter to improve perf ?
		//Set the window handle ?
		GetMessage(&msg, NULL, 0, 0);

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	DestroyWindow(m_windowHandle);
	m_wglContext.destroy();
}

} //namespace window
