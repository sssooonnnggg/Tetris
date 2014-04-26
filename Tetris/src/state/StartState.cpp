#include "state/StartState.h"
#include "UIManager.h"
#include "ui/GameUI.h"
#include "ui/Button.h"
#include "ui/Label.h"

#include "Animation.h"

#include "action/Action.h"

StartState::StartState(GameManager* gm, Renderer* renderer)
	: GameState(gm, renderer)
	, m_startUI(NULL)
	, m_actStart(NULL)
	, m_cutscene(NULL)
{
	CreateUI();
	m_cutscene = new BlockAnimation(renderer);
}

void StartState::CreateUI()
{
	m_startUI = new UIManager;
	Label* title = new Label(m_renderer, Rect(0, 0, WindowWidth, WindowHeight * 0.3), L"俄罗斯方块");
	Button* start = new Button(m_renderer, Rect(ButtonX, WindowHeight * 0.4, ButtonWidth, ButtonHeight), L"开始游戏");
	Button* help = new Button(m_renderer, Rect(ButtonX, WindowHeight * 0.55, ButtonWidth, ButtonHeight), L"游戏帮助");
	Button* about = new Button(m_renderer, Rect(ButtonX, WindowHeight * 0.7, ButtonWidth, ButtonHeight), L"关于");

	m_actStart = new StartAction(m_gm);
	start->SetAction(m_actStart);

	m_startUI->RegisterUI(title);
	m_startUI->RegisterUI(start);
	m_startUI->RegisterUI(help);
	m_startUI->RegisterUI(about);
}

StartState::~StartState()
{
	delete m_startUI;
	delete m_actStart;
	delete m_cutscene;
}

std::wstring StartState::Name()
{
	return L"start";
}

void StartState::Draw()
{
	m_cutscene->Draw();
	m_startUI->Draw();
}

void StartState::Notify(Event* e)
{
	if ( Event::MOUSE != e->Type() )
		return;

	MouseEvent* mouseEvent = static_cast<MouseEvent*>(e);

	m_startUI->Notify(mouseEvent);
}