/*!
	Description : Abstract game's state
	Author		: Ruining Song
	Date		: 2014/3/12
*/

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Base.h"
#include <string>

class GameManager;
class Renderer;

class GameState
{
public:
	GameState(GameManager* gm, Renderer* renderer)
		: m_gm(gm)
		, m_renderer(renderer)
	{}

	virtual ~GameState(){}

	/*!
	\brief
		In this function, do something initialzation.
	*/
	virtual void Init(){}
	virtual std::wstring Name() = 0;

	virtual void Update(){}
	virtual void Draw(){}
	virtual void Notify(Event* e){};

	/*!
	\brief
		Reset the state.
	*/
	virtual void Reset(){}

protected:
	GameManager* m_gm;
	Renderer* m_renderer;
};

#endif // GAMESTATE_H