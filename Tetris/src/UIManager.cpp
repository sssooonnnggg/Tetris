#include "UIManager.h"
#include "Utils.h"
#include "ui/GameUI.h"

UIManager::~UIManager()
{
	UIList::iterator it = m_UIList.begin();

	while ( it != m_UIList.end() )
	{
		delete (*it);
		++it;
	}
}

void UIManager::RegisterUI(GameUI* ui)
{
	m_UIList.push_back(ui);
}

void UIManager::RemoveUI(GameUI* ui)
{
	UIList::iterator it = m_UIList.begin();

	while ( it != m_UIList.end() )
	{
		if ( ui == *it )
		{
			delete ui;
			m_UIList.erase(it);
			return;
		}
		
		++it;
	}
}

void UIManager::Notify(MouseEvent* event)
{
	if ( MouseEvent::MOUSE_BUTTON_CLICKED == event->GetMouseEventType() )
	{
		GameUI* ui = FindUI(event->GetPos());

		if ( NULL != ui )
			ui->Update(event);
	}
	else
	{
		//< BroadCast mouse move event to all controls so
		//< that it can change hover/normal state.
		UIList::iterator it = m_UIList.begin();

		while ( it != m_UIList.end() )
		{
			(*it)->Update(event);
			++it;
		}
	}
}

GameUI* UIManager::FindUI(const Point& point)
{
	UIList::iterator it = m_UIList.begin();

	while ( it != m_UIList.end() )
	{
		if ( PointInRect(point, (*it)->GetRect()) )
			return (*it);

		++it;
	}

	return NULL;
}

void UIManager::Draw()
{
	UIList::iterator it = m_UIList.begin();

	while ( it != m_UIList.end() )
	{
		(*it)->Draw();
		++it;
	}
}