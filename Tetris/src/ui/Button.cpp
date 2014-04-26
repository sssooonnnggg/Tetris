#include "ui/Button.h"
#include "SDLRenderer.h"
#include "Utils.h"

#include "action/Action.h"

Button::Button(Renderer* renderer, const Rect& rect, std::wstring text)
	: GameUI(renderer)
	, m_rect(rect)
	, m_text(text)
	, m_status(NORMAL)
{
	m_renderer->SetFont(L"buttonfont");
	m_idHover = m_renderer->CreateText(m_text.c_str(), ColorWhite);
	m_idNormal = m_renderer->CreateText(m_text.c_str(), ColorBlue);
}

void Button::Draw()
{
	if ( HOVER == m_status )
		m_renderer->FillRect(m_rect, ColorBlue);

	if ( HOVER == m_status )
		m_renderer->RenderText(m_idHover, m_rect);
	else
		m_renderer->RenderText(m_idNormal, m_rect);
}

void Button::Update(MouseEvent* event)
{
	if ( MouseEvent::MOUSE_BUTTON_CLICKED == event->GetMouseEventType() )
	{
		Action* act = GetAction();

		if ( NULL != act )
			(*act)();
	}

	if ( MouseEvent::MOUSE_MOVE == event->GetMouseEventType() )
		m_status = PointInRect(event->GetPos(), m_rect) ? HOVER : NORMAL;
}

const Rect& Button::GetRect()
{
	return m_rect;
}