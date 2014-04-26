#include "ui/Label.h"
#include "SDLRenderer.h"

Label::Label(Renderer* renderer, const Rect& rect, std::wstring text, Color color, std::wstring font)
	: GameUI(renderer)
	, m_rect(rect)
	, m_text(text)
	, m_color(color)
{
	m_renderer->SetFont(font);
	m_id = m_renderer->CreateText(text.c_str(), m_color);
	m_type = TEXT_LABEL;
}

Label::Label(Renderer* renderer, const Rect& rect, const char* picPath)
	: GameUI(renderer)
	, m_rect(rect)
	, m_color(ColorRed)
{
	m_id = m_renderer->CreatePicture(picPath);
	m_type = PICTURE_LABEL;
}

void Label::Draw()
{
	if ( TEXT_LABEL == m_type )
		m_renderer->RenderText(m_id, m_rect);
	else
		m_renderer->RenderPicture(m_id, m_rect);
}

void Label::SetText(std::wstring text)
{
	m_renderer->DestroyText(m_id);
	m_text = text;
	m_id = m_renderer->CreateText(m_text.c_str(), m_color);
}

const Rect& Label::GetRect()
{
	return m_rect;
}