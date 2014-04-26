/*!
	Description : The game main frame
	Author		: Ruining Song
	Date		: 2014/3/8
*/

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SDL.h>
#include <list>

#include "Base.h"

class Renderer;
class EventHandler;
class UIManager;

class GameState;

class Label;

class GameManager
{
public:

	GameManager();
	virtual ~GameManager();

	virtual void Init();
	virtual void CreateRenderer(){}
	virtual void CreateEventHandler(){}

	void Loop();
	void Update();
	void Draw();

	GameState* GetStartState();
	GameState* GetRunningState();
	GameState* GetPauseState();
	GameState* GetEndState();
	GameState* GetExitState();
	void SetState(GameState* state);

	void ProcessEvent(Event* event);

private:
	void InitResource();
	void InitStates();

protected:
	Renderer* m_renderer;
	EventHandler* m_eventHandler;

	/*!
	\brief
		Game states.
	*/
	GameState* m_state;
	GameState* m_startState;
	GameState* m_runningState;
	GameState* m_pauseState;
	GameState* m_endState;
	GameState* m_exitState;

	Label* m_bg;
};

class SDLGameManager : public GameManager
{
public:
	~SDLGameManager();
	void Init();
	void CreateRenderer();
	void CreateEventHandler();

protected:
	SDL_Window* m_window;
};
#endif