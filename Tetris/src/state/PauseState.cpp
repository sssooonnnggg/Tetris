#include "state/PauseState.h"
#include "UIManager.h"
#include "ui/GameUI.h"
#include "ui/Button.h"
#include "ui/Label.h"

#include "action/Action.h"

PauseState::PauseState(GameManager* gm, Renderer* renderer)
	: GameState(gm, renderer)
	, m_pauseUI(NULL)
	, m_actResume(NULL)
	, m_actRestart(NULL)
{
	CreateUI();
}

void PauseState::CreateUI()
{
	///< pause ui
	m_pauseUI = new UIManager;
	Label* pause = new Label(m_renderer, Rect(0, 0, WindowWidth, WindowHeight * 0.3), L"暂停");
	Button* resume = new Button(m_renderer, Rect(ButtonX, WindowHeight * 0.4, ButtonWidth, ButtonHeight), L"继续游戏");
	Button* restartGame = new Button(m_renderer, Rect(ButtonX, WindowHeight * 0.55, ButtonWidth, ButtonHeight), L"重新开始");

	m_actResume = new ResumeAction(m_gm);
	resume->SetAction(m_actResume);
	m_actRestart = new StartAction(m_gm);
	restartGame->SetAction(m_actRestart);

	m_pauseUI->RegisterUI(pause);
	m_pauseUI->RegisterUI(resume);
	m_pauseUI->RegisterUI(restartGame);
}

PauseState::~PauseState()
{
	delete m_pauseUI;
	delete m_actResume;
	delete m_actRestart;
}

std::wstring PauseState::Name()
{
	return L"pause";
}

void PauseState::Draw()
{
	m_pauseUI->Draw();
}

void PauseState::Notify(Event* e)
{
	if ( Event::MOUSE != e->Type() )
		return;

	MouseEvent* mouseEvent = static_cast<MouseEvent*>(e);

	m_pauseUI->Notify(mouseEvent);
}