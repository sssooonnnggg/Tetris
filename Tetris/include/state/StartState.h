/*!
	Description : Brief the state "Start" of the game
	Author		: Ruining Song
	Date		: 2014/04/24
*/

#ifndef STARTSTATE_H
#define STARTSTATE_H

#include "GameState.h"

class UIManager;
class StartAction;
class BlockAnimation;

class StartState : public GameState
{
public:
	StartState(GameManager* gm, Renderer* renderer);
	~StartState();

	std::wstring Name();
	void Draw();

	void Notify(Event* e);

private:
	void CreateUI();

private:
	UIManager* m_startUI;
	StartAction* m_actStart;
	BlockAnimation* m_cutscene;
};

#endif // STARTSTATE_H
	