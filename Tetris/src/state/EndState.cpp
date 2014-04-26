#include "state/EndState.h"
#include "UIManager.h"
#include "ui/GameUI.h"
#include "ui/Button.h"
#include "ui/Label.h"

#include "action/Action.h"

EndState::EndState(GameManager* gm, Renderer* renderer)
: GameState(gm, renderer)
	, m_endUI(NULL)
	, m_actRestart(NULL)
	, m_actMainMenu(NULL)
{
	CreateUI();
}

void EndState::CreateUI()
{
	///< end ui
	m_endUI = new UIManager;
	Label* gameover = new Label(m_renderer, Rect(0, 0, WindowWidth, WindowHeight * 0.3), L"游戏结束");
	Button* restart = new Button(m_renderer, Rect(ButtonX, WindowHeight * 0.4, ButtonWidth, ButtonHeight), L"重新开始");
	Button* returnStartUI = new Button(m_renderer, Rect(ButtonX, WindowHeight * 0.55, ButtonWidth, ButtonHeight), L"返回主界面");

	m_actRestart = new StartAction(m_gm);
	restart->SetAction(m_actRestart);
	m_actMainMenu = new MainMenuAction(m_gm);
	returnStartUI->SetAction(m_actMainMenu);

	m_endUI->RegisterUI(gameover);
	m_endUI->RegisterUI(restart);
	m_endUI->RegisterUI(returnStartUI);
}

EndState::~EndState()
{
	delete m_endUI;
	delete m_actRestart;
	delete m_actMainMenu;
}

std::wstring EndState::Name()
{
	return L"end";
}

void EndState::Draw()
{
	m_endUI->Draw();
}

void EndState::Notify(Event* e)
{
	if ( Event::MOUSE != e->Type() )
		return;

	MouseEvent* mouseEvent = static_cast<MouseEvent*>(e);

	m_endUI->Notify(mouseEvent);
}