/*!
	Description : Handle user input
	Author		: Ruining Song
	Date		: 2014/3/8
*/

#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SDL.h>

class GameManager;

class EventHandler
{
public:
	EventHandler(GameManager* gm)
		: m_gm(gm)
	{}

	virtual void DoEvent() = 0;

protected:
	GameManager* m_gm;

};

class SDLEventHandler : public EventHandler
{
public:
	SDLEventHandler(GameManager* gm)
		: EventHandler(gm)
	{}

	void DoEvent();

private:
	void ProcessEvent();
	void ProcessWindowEvent();
	void ProcessKeyEvent();
	void ProcessKeyDownEvent();
	void ProcessKeyUpEvent();
	void ProcessMouseEvent();

private:
	SDL_Event m_event;
};

#endif // EVENTHANDLER_H