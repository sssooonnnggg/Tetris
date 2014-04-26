/*!
	Description : Brief the state "end" of the game.
	Author		: Ruining Song
	Date		: 2014/04/24
*/

#ifndef ENDSTATE_H
#define ENDSTATE_H

#include "GameState.h"

class UIManager;
class StartAction;
class MainMenuAction;

class EndState : public GameState
{
public:
	EndState(GameManager* gm, Renderer* renderer);
	~EndState();

	std::wstring Name();
	void Draw();

	void Notify(Event* e);

private:
	void CreateUI();

private:
	UIManager* m_endUI;
	StartAction* m_actRestart;
	MainMenuAction* m_actMainMenu;
};

#endif // ENDSTATE_H