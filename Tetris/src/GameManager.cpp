#include "GameManager.h"
#include "SDLRenderer.h"
#include "EventHandler.h"
#include "Utils.h"

#include "state/GameState.h"
#include "state/StartState.h"
#include "state/PauseState.h"
#include "state/RunningState.h"
#include "state/EndState.h"
#include "state/ExitState.h"

#include "ui/Label.h"

#include <algorithm>

GameManager::GameManager()
	: m_renderer(NULL)
	, m_eventHandler(NULL)
	, m_state(NULL)
	, m_startState(NULL)
	, m_runningState(NULL)
	, m_pauseState(NULL)
	, m_endState(NULL)
	, m_exitState(NULL)
	, m_bg(NULL)
{	

}

GameManager::~GameManager()
{
	delete m_renderer;
	delete m_eventHandler;

	delete m_startState;
	delete m_runningState;
	delete m_pauseState;
	delete m_endState;
	delete m_exitState;

	delete m_bg;
}

void GameManager::Init()
{
	CreateRenderer();
	InitResource();
	CreateEventHandler();
	InitStates();
}

void GameManager::InitStates()
{
	m_startState = new StartState(this, m_renderer);
	m_runningState = new RunningState(this, m_renderer);
	m_pauseState = new PauseState(this, m_renderer);
	m_endState = new EndState(this, m_renderer);
	m_exitState = new ExitState(this, m_renderer);

	SetState(m_startState);
}

void GameManager::InitResource()
{
	m_bg = new Label(m_renderer, Rect(0, 0, WindowWidth, WindowHeight), "bg.png");
	m_renderer->AddFont(L"scorefont", "FZYTK.TTF", 28);
	m_renderer->AddFont(L"labelfont", "FZYTK.TTF", 50);
	m_renderer->AddFont(L"buttonfont", "FZYTK.TTF", 28);
}

void GameManager::SetState(GameState* state)
{
	m_state = state;
	m_state->Init();
}

GameState* GameManager::GetStartState()
{
	return m_startState;
}

GameState* GameManager::GetRunningState()
{
	return m_runningState;
}

GameState* GameManager::GetPauseState()
{
	return m_pauseState;
}

GameState* GameManager::GetEndState()
{
	return m_endState;
}

GameState* GameManager::GetExitState()
{
	return m_exitState;
}

void GameManager::Loop()
{
	while ( L"exit" != m_state->Name() )
	{
		m_eventHandler->DoEvent();
		
		Update();
		Draw();
	}
}

void GameManager::Update()
{
	m_state->Update();
}

void GameManager::Draw()
{
	m_renderer->DrawBackground(ColorBackGround);
	m_bg->Draw();
	m_state->Draw();
	m_renderer->BeginRender();
}

void GameManager::ProcessEvent(Event* event)
{
	if ( event->Type() == Event::WINDOW )
	{
		WindowEvent* winEvent = static_cast<WindowEvent*>(event);
		
		if ( WindowEvent::WINDOW_CLOSE == winEvent->GetWindowEventType() )
		{
			SetState(GetExitState());
			return;
		}
	}

	m_state->Notify(event);
}


SDLGameManager::~SDLGameManager()
{
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void SDLGameManager::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow("Tetris", GetWindowX(), GetWindowY(), WindowWidth, WindowHeight, SDL_WINDOW_SHOWN);
	GameManager::Init();
}

void SDLGameManager::CreateRenderer()
{
	m_renderer = new SDLRenderer(m_window);
}

void SDLGameManager::CreateEventHandler()
{
	m_eventHandler = new SDLEventHandler(this);
}