/*!
	Description : Game UI
	Author		: Ruining Song
	Date		: 2014/3/11
*/

#ifndef GAMEUI_H
#define GAMEUI_H

#include "entity/GameObject.h"

/*!
\brief
	Base class of Game UI control.
*/
class Action;
class GameUI : public GameObject
{
public:
	GameUI(Renderer* renderer)
		: GameObject(renderer)
		, m_action(NULL)
	{}

	virtual void Update(MouseEvent* event) = 0;
	virtual const Rect& GetRect() = 0;

	void SetAction(Action* action);

protected:
	Action* GetAction();

private:
	Action* m_action;
};

#endif // GAMEUI_H