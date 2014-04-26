/*!
	Description : This class abstracts a "label".
	Author		: Ruining Song
	Date		: 2014/04/25
*/
#ifndef LABEL_H
#define LABEL_H

#include "ui/GameUI.h"

class Label : public GameUI
{
public:

	enum LabelType{TEXT_LABEL, PICTURE_LABEL};
	Label(Renderer* renderer, const Rect& rect, std::wstring text, Color color = ColorRed, std::wstring font = L"labelfont");
	Label(Renderer* renderer, const Rect& rect, const char* picPath);

	virtual void Draw();
	void Update(MouseEvent* event){}
	const Rect& GetRect();

	void SetText(std::wstring text);

protected:
	std::wstring m_text;
	Rect m_rect;
	Color m_color;
	std::wstring m_id;
	LabelType m_type;
};

#endif // LABEL_H