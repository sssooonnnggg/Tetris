/*!
	Description : This class abstracts a "button".
	Author		: Ruining Song
	Date		: 2014/04/25
*/

#ifndef BUTTON_H
#define BUTTON_H


#include "ui/GameUI.h"
class Button : public GameUI
{
public:

	Button(Renderer* renderer, const Rect& rect, std::wstring text = L"");

	void Draw();
	void Update(MouseEvent* event);
	const Rect& GetRect();

	enum ButtonStatus{HOVER, NORMAL};

private:
	Rect m_rect;
	std::wstring m_text;
	ButtonStatus m_status;
	std::wstring m_idHover;
	std::wstring m_idNormal;
};

#endif // BUTTON_H