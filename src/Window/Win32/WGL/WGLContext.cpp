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

#include "GameEngine/Common/Debug/Logger.h"
#include "GameEngine/Window/Win32/WGL/WGLContext.h"
#include "GameEngine/Window/Window.h"
#include <gl/GL.h>
#include "GL\wglext.h"

using namespace common;

namespace window
{

GAME_ENGINE_EXPORT WGLContext::WGLContext(WindowAttributes* const attributes) :
	Win32Window(attributes)
{
	m_hdc = GetDC(m_windowHandle);

	m_hglrc = 0;
	PIXELFORMATDESCRIPTOR pfd;

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cAlphaBits = 0;
	pfd.cAccumBits = 0; //No accumulation buffer
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0; //No stencil buffer
	pfd.cAuxBuffers = 0; //No auxiliary buffer
	pfd.iLayerType = PFD_MAIN_PLANE;

	int pixelFormat = ChoosePixelFormat(m_hdc, &pfd);
	if(pixelFormat == 0)
		throw exception::PixelFormatNotFound(__FILE__, __LINE__ - 2);
	else
	{
		SetPixelFormat(m_hdc, pixelFormat, &pfd);
		m_hglrc = wglCreateContext(m_hdc);
		wglMakeCurrent(m_hdc, m_hglrc);

		if(attributes->openGLVersion[0] > 21) //21 -> OpenGL 2.1
		{
			PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB =
			reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>
			(wglGetProcAddress("wglChoosePixelFormatARB"));

			if(wglChoosePixelFormatARB == NULL)
				Logger::logInfo()("Failed to get extension wglChoosePixelFormat"
				                  "ARB. OpenGL 2.1 will be used.");
			else
			{
				PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB
				= reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>
				(wglGetProcAddress("wglCreateContextAttribsARB"));

				if(wglCreateContextAttribsARB == NULL)
					Logger::logInfo()("Failed to get extension wglCreateContext"
								      "AttribsARB. OpenGL 2.1 will be used.");
				else
				{
					int glAttribsList[5];
					glAttribsList[0] = WGL_CONTEXT_MAJOR_VERSION_ARB;
					glAttribsList[2] = WGL_CONTEXT_MINOR_VERSION_ARB;
					glAttribsList[4] = 0;

					unsigned char i(0);
					for(; i < attributes->version; i++)
					{
						glAttribsList[1] = attributes->openGLVersion[i] / 10;
						glAttribsList[3] = attributes->openGLVersion[i] % 10;

						m_hglrc = wglCreateContextAttribsARB(m_hdc, 0,
						                                     glAttribsList);
						if(m_hglrc != NULL)
						{
							i = attributes->version;
							break;
						}

						if(i == attributes->version - 1)
							throw exception::BadOpenGLVersion(glAttribsList[1],
							                                  glAttribsList[3]);
					}

					attributes->version = attributes->openGLVersion[i];
					wglMakeCurrent(m_hdc, m_hglrc);
					Logger::logInfo()("OpenGL %s will be used",
					                  glGetString(GL_VERSION));
				}
			}
		}
		else if(attributes->openGLVersion[0] < 21)
			Logger::logWarning()("Attempt to create an OpenGL %.1f context. Ope"
			                     "nGL 2.1 will be used.",
								 *attributes->openGLVersion / 10.0f);
		else
			Logger::logInfo()("OpenGL 2.1 will be used");
	}
}

GAME_ENGINE_EXPORT WGLContext::~WGLContext()
{
	if(m_hglrc != 0)
	{
		wglMakeCurrent(m_hdc, 0);
		wglDeleteContext(m_hglrc);
		ReleaseDC(m_windowHandle, m_hdc);
	}
}

namespace exception
{

GAME_ENGINE_EXPORT PixelFormatNotFound::PixelFormatNotFound(
	const char* const pFile, uint16_t const pLine)
{
	//Use memcpy ?
	file = pFile;
	line = pLine;
}

GAME_ENGINE_EXPORT BadOpenGLVersion::BadOpenGLVersion(char const pMinorVersion,
													  char const pMajorVersion)
{
	minorVersion = pMinorVersion;
	majorVersion = pMajorVersion;
}

}

}; //namespace window