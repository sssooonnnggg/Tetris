#include "ui/GameUI.h"

void GameUI::SetAction(Action* action)
{
	m_action = action;
}

Action* GameUI::GetAction()
{
	return m_action;
}