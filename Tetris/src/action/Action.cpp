#include "action/Action.h"
#include "GameManager.h"
#include "state/GameState.h"

StartAction::StartAction(GameManager* gm)
: m_gm(gm)
{

}

void StartAction::operator()()
{
	// Reset the running state first.
	m_gm->GetRunningState()->Reset();
	m_gm->SetState(m_gm->GetRunningState());
}

ResumeAction::ResumeAction(GameManager* gm)
: m_gm(gm)
{

}

void ResumeAction::operator()()
{
	m_gm->SetState(m_gm->GetRunningState());
}

MainMenuAction::MainMenuAction(GameManager* gm)
: m_gm(gm)
{

}

void MainMenuAction::operator()()
{
	m_gm->SetState(m_gm->GetStartState());
}