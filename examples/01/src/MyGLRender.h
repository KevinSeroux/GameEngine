/*------------------------------------------------------------------------------
| DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE                                  |
| Version 2, December 2004                                                     |
|                                                                              |
| Copyright (C) 2013  Kévin Seroux <kevin.seroux@orange.fr>                    |
|                                                                              |
| Everyone is permitted to copy and distribute verbatim or modified copies of  |
| this license document, and changing it is allowed as long as the name is     |
| changed.                                                                     |
|                                                                              |
| DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE                                  |
| TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION              |
|                                                                              |
| 0. You just DO WHAT THE FUCK YOU WANT TO.                                    |
\-----------------------------------------------------------------------------*/

#ifndef MY_GL_RENDER__H
#define MY_GL_RENDER__H

#include "GameEngine/Window/Window.h"

//Forward declarations
namespace window
{
	class Event;
}

class MyGLRender : public window::Window
{
public:
	void onEvent(window::Event const * const p_event);

	float const getGreen() const;
	float const getBlue() const;

private:
	float m_green, m_blue;
};

inline float const MyGLRender::getGreen() const
{
	return m_green;
}

inline float const MyGLRender::getBlue() const
{
	return m_blue;
}

#endif //MY_GL_RENDER__H