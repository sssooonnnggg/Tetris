/*!
	Description : Brief the state "exit" of the game.
	Author		: Ruining Song
	Date		: 2014/04/25
*/
#ifndef EXITSTATE_H
#define EXITSTATE_H

#include "state/GameState.h"

class ExitState : public GameState
{
public:
	ExitState(GameManager* gm, Renderer* renderer)
		: GameState(gm, renderer)
	{}

	std::wstring Name()
	{
		return L"exit";
	}
};

#endif // EXITSTATE_H