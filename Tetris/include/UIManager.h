/*!
	Description : UI manager
	Author		: Ruining Song
	Date		: 2014/3/11
*/

#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <list>
#include "Base.h"

class GameUI;

class UIManager
{
public:
	void RegisterUI(GameUI* ui);
	void RemoveUI(GameUI* ui);
	void Notify(MouseEvent* event);
	void Draw();

	~UIManager();

private:
	GameUI* FindUI(const Point& point);

protected:
	typedef std::list<GameUI*> UIList;
	UIList m_UIList;
};

#endif // UIMANAGER_H