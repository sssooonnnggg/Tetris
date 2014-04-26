#include "GameManager.h"
#include "EventHandler.h"

#include "ui/GameUI.h"

void SDLEventHandler::DoEvent()
{
	while ( SDL_PollEvent(&m_event) )
		ProcessEvent();
}

void SDLEventHandler::ProcessEvent()
{
	switch ( m_event.type )
	{
	case SDL_WINDOWEVENT:
		ProcessWindowEvent();
		break;
	case SDL_KEYUP:
	case SDL_KEYDOWN:
		ProcessKeyEvent();
		break;
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONUP:
		ProcessMouseEvent();
		break;
	}
}

void SDLEventHandler::ProcessWindowEvent()
{
	switch ( m_event.window.event )
	{
	case SDL_WINDOWEVENT_CLOSE:
		WindowEvent e(WindowEvent::WINDOW_CLOSE);
		m_gm->ProcessEvent(&e);
		break;
	}
}

void SDLEventHandler::ProcessKeyEvent()
{
	if ( SDL_PRESSED == m_event.key.state )
		ProcessKeyDownEvent();
	else
		ProcessKeyUpEvent();
}

void SDLEventHandler::ProcessKeyDownEvent()
{
	switch ( m_event.key.keysym.sym )
	{
	case SDLK_LEFT:
		{
			KeyboardEvent e(KeyboardEvent::KEY_LEFT, true);
			m_gm->ProcessEvent(&e);
		}
		break;
	case SDLK_RIGHT:
		{
			KeyboardEvent e(KeyboardEvent::KEY_RIGHT, true);
			m_gm->ProcessEvent(&e);
		}
		break;
	case SDLK_DOWN:
		{
			KeyboardEvent e(KeyboardEvent::KEY_DOWN, true);
			m_gm->ProcessEvent(&e);
		}
		break;
	case SDLK_UP:
		{
			KeyboardEvent e(KeyboardEvent::KEY_UP, true);
			m_gm->ProcessEvent(&e);
		}
		break;
	case SDLK_SPACE:
		{
			KeyboardEvent e(KeyboardEvent::KEY_SPACE, true);
			m_gm->ProcessEvent(&e);
		}
		break;
	case SDLK_ESCAPE:
		{
			KeyboardEvent e(KeyboardEvent::KEY_ESCAPE, true);
			m_gm->ProcessEvent(&e);
		}
		break;
	}
}

void SDLEventHandler::ProcessKeyUpEvent()
{
	switch ( m_event.key.keysym.sym )
	{
	case SDLK_DOWN:
		{
			KeyboardEvent e(KeyboardEvent::KEY_DOWN, false);
			m_gm->ProcessEvent(&e);
		}
		break;
	}
}

void SDLEventHandler::ProcessMouseEvent()
{

	switch ( m_event.type )
	{
	case SDL_MOUSEMOTION:
		{
			MouseEvent e(MouseEvent::MOUSE_MOVE, Point(m_event.motion.x, m_event.motion.y));
			m_gm->ProcessEvent(&e);
		}
		break;
	case SDL_MOUSEBUTTONUP:
		{
			MouseEvent e(MouseEvent::MOUSE_BUTTON_CLICKED, Point(m_event.motion.x, m_event.motion.y));
			m_gm->ProcessEvent(&e);
		}
		break;
	}
}