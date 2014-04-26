/*!
	Description : Brief the state "pause" of the game.
	Author		: Ruining Song
	Date		: 2014/04/24
*/

#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "GameState.h"

class UIManager;
class ResumeAction;
class StartAction;

class PauseState : public GameState
{
public:
	PauseState(GameManager* gm, Renderer* renderer);
	~PauseState();

	std::wstring Name();
	void Draw();

	void Notify(Event* e);

private:
	void CreateUI();

private:
	UIManager* m_pauseUI;
	ResumeAction* m_actResume;
	StartAction* m_actRestart;
};

#endif // PAUSESTATE_H