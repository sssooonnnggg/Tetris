#include "state/RunningState.h"
#include "GameManager.h"

#include "ui/Label.h"
#include "UIManager.h"

#include "entity/Block.h"
#include "entity/Pools.h"

#include "Utils.h"

#include <Windows.h>

RunningState::RunningState(GameManager* gm, Renderer* renderer, unsigned int interval)
	: GameState(gm, renderer)
	, m_interval(interval)
	, m_softdropInterval(SoftDropInterval)
	, m_onSoftdrop(false)
	, m_topLeft(Point(50, 50))
	, m_levelText(NULL)
	, m_scoreText(NULL)
	, m_lineText(NULL)
	, m_indicator(NULL)
{
	CreateScoreUI();
	InitBlockQueue();
	CreateBlock();
	CreatePools();
	UpdateIndicator();
}

RunningState::~RunningState()
{
	BlockQueue::iterator it = m_blockQueue.begin();

	while ( it != m_blockQueue.end() )
	{
		delete *it;
		++it;
	}

	if ( m_indicator )
		delete m_indicator;

	delete m_pools;
	delete m_scoreUI;
}

void RunningState::CreateScoreUI()
{
	m_scoreUI = new UIManager;

	Label* currentLevel = new Label(m_renderer, Rect(450, 50, 200, 50), L"当前关卡", ColorBlue, L"scorefont");
	m_levelText = new Label(m_renderer, Rect(450, 100, 200, 50), IntToStr(m_scroInfo.m_level), ColorMango, L"scorefont");
	Label* currentLine = new Label(m_renderer, Rect(450, 200, 200, 50), L"已消行数", ColorBlue, L"scorefont");
	m_lineText = new Label(m_renderer, Rect(450, 250, 200, 50), IntToStr(m_scroInfo.m_line), ColorMango, L"scorefont");
	Label* currentScore = new Label(m_renderer, Rect(450, 350, 200, 50), L"分数", ColorBlue, L"scorefont");
	m_scoreText = new Label(m_renderer, Rect(450, 400, 200, 50), IntToStr(m_scroInfo.m_score), ColorMango, L"scorefont");

	m_scoreUI->RegisterUI(currentScore);
	m_scoreUI->RegisterUI(m_scoreText);
	m_scoreUI->RegisterUI(currentLevel);
	m_scoreUI->RegisterUI(m_levelText);
	m_scoreUI->RegisterUI(currentLine);
	m_scoreUI->RegisterUI(m_lineText);
}

void RunningState::CreateBlock()
{
	Point blockPos[BlockQueueSize] = 
	{Point(BlockUnitWidth*(PoolsWidth/2-1), 0), Point(NextBlockX-m_topLeft.x, 0), Point(NextBlockX-m_topLeft.x, 120)};

	delete m_blockQueue.front();
	m_blockQueue.pop_front();

	BlockQueue::iterator it = m_blockQueue.begin();
	int i = 0;

	while ( it != m_blockQueue.end() )
	{
		(*it)->Move(blockPos[i]-blockPos[i+1]);
		it++;
		i++;
	}

	Block* tail = Block::CreateBlock(m_renderer, m_topLeft);
	tail->Move(blockPos[i]);
	m_blockQueue.push_back(tail);

	// Create indicator.
	if ( m_indicator ) delete m_indicator;
	m_indicator = new Block(*(m_blockQueue.front()));
	m_indicator->SetOpacity(IndicatorOpacity);
}

void RunningState::CreatePools()
{
	m_pools = new Pools(m_renderer, m_topLeft, PoolsWidth, PoolsHeight);
}

std::wstring RunningState::Name()
{
	return L"running";
}

void RunningState::Init()
{
	m_lastTickcount = GetTickCount();
}

void RunningState::Reset()
{
	// Ensure "soft drop" is off.
	SetSoftDrop(false);

	m_pools->Reset();

	BlockQueue::iterator it = m_blockQueue.begin();

	while ( it != m_blockQueue.end() )
	{
		delete *it;
		++it;
	}

	InitBlockQueue();
	CreateBlock();
	UpdateIndicator();
}

void RunningState::InitBlockQueue()
{
	Point blockPos[BlockQueueSize] = 
	{Point(BlockUnitWidth*(PoolsWidth/2-1), 0), Point(NextBlockX-m_topLeft.x, 0), Point(NextBlockX-m_topLeft.x, 120)};

	std::srand(GetTickCount());

	m_blockQueue.clear();

	for ( int i = 0; i < BlockQueueSize; ++i )
	{
		Block* block = Block::CreateBlock(m_renderer, m_topLeft);
		block->Move(blockPos[i]);
		m_blockQueue.push_back(block);
	}
}

void RunningState::Draw()
{
	m_pools->Draw();

	BlockQueue::iterator it = m_blockQueue.begin();

	while ( it != m_blockQueue.end() )
	{
		(*it)->Draw();
		++it;
	}

	m_indicator->Draw();
	m_scoreUI->Draw();
}

void RunningState::Update()
{
	if ( FrameChange() ) 
		MoveBlockDown();

	UpdateScore();

	if ( m_pools->IsFullFilled() )
		m_gm->SetState(m_gm->GetEndState());
}

bool RunningState::FrameChange()
{
	unsigned int interval = m_onSoftdrop ? m_softdropInterval : m_interval;

	if ( GetTickCount() - m_lastTickcount >= interval )
	{
		m_lastTickcount = GetTickCount();
		return true;
	}

	return false;
}

void RunningState::MoveBlockDown()
{
	m_blockQueue.front()->MoveDown();

	if ( TouchBound(m_blockQueue.front()) )
	{
		m_blockQueue.front()->MoveUp();
		UpdatePools();
		CreateBlock();
		UpdateIndicator();
	}
}

void RunningState::UpdatePools()
{
	const BlockUnit* unit = m_blockQueue.front()->GetFirstBlock();

	while ( NULL != unit )
	{
		int column = (unit->x - m_topLeft.x) / BlockUnitWidth;
		int row = (unit->y - m_topLeft.y) / BlockUnitHeight;

		m_pools->SetFilled(row, column, unit->color);

		unit = m_blockQueue.front()->GetNextBlock();
	}
}

bool RunningState::TouchBound(Block* block)
{
	const BlockUnit* unit = block->GetFirstBlock();

	while ( NULL != unit )
	{
		int column = (unit->x - m_topLeft.x) / BlockUnitWidth;
		int row = (unit->y - m_topLeft.y) / BlockUnitHeight;

		if ( m_pools->IsFilled(row, column) )
			return true;

		unit = block->GetNextBlock();
	}

	return false;
}

void RunningState::UpdateIndicator()
{
	m_indicator->Copy(m_blockQueue.front());
	m_indicator->SetOpacity(IndicatorOpacity);

	while ( !TouchBound(m_indicator) )
		m_indicator->MoveDown();

	m_indicator->MoveUp();
}

void RunningState::UpdateScore()
{
	int rowCleared = m_pools->Clear();

	if ( !rowCleared ) return;

	m_scroInfo.m_line += rowCleared;
	m_scroInfo.m_score += ScoreFactor[rowCleared-1];

	if ( m_scroInfo.m_line >= m_scroInfo.m_level * 10 + 10 )
		++m_scroInfo.m_level;

	m_scoreText->SetText(IntToStr(m_scroInfo.m_score));
	m_levelText->SetText(IntToStr(m_scroInfo.m_level));
	m_lineText->SetText(IntToStr(m_scroInfo.m_line));

	SetInterval(LevelInterval[m_scroInfo.m_level]);
}

void RunningState::Notify(Event* e)
{
	if ( Event::KEYBOARD != e->Type() )
		return;

	KeyboardEvent* keyEvent = static_cast<KeyboardEvent*>(e);
	int keyType = keyEvent->GetKeyboardEventType();

	if ( KeyboardEvent::KEY_LEFT == keyType )
		OnPressLeft();
	else if ( KeyboardEvent::KEY_RIGHT == keyType )
		OnPressRight();
	else if ( KeyboardEvent::KEY_UP == keyType )
		OnPressUp();
	else if ( KeyboardEvent::KEY_SPACE == keyType )
		OnPressSpace();
	else if ( KeyboardEvent::KEY_ESCAPE == keyType )
		OnPressEscape();
	else if ( KeyboardEvent::KEY_DOWN == keyType
		&& keyEvent->IsPressed() )
		OnPressDown();
	else if ( KeyboardEvent::KEY_DOWN == keyType
		&& ( !keyEvent->IsPressed() ) )
		OnReleaseDown();
}

void RunningState::OnPressLeft()
{
	m_blockQueue.front()->MoveLeft();

	if ( TouchBound(m_blockQueue.front()) )
		m_blockQueue.front()->MoveRight();

	UpdateIndicator();
}

void RunningState::OnPressRight()
{
	m_blockQueue.front()->MoveRight();

	if ( TouchBound(m_blockQueue.front()) )
		m_blockQueue.front()->MoveLeft();

	UpdateIndicator();
}

void RunningState::OnPressDown()
{
	SetSoftDrop(true);
}

void RunningState::SetSoftDrop(bool onSoftdrop)
{
	m_onSoftdrop = onSoftdrop;
}

void RunningState::OnReleaseDown()
{
	SetSoftDrop(false);
}

void RunningState::OnPressSpace()
{
	// Move block down until touching bottom.
	while ( !TouchBound(m_blockQueue.front()) )
		m_blockQueue.front()->MoveDown();

	m_blockQueue.front()->MoveUp();
	UpdatePools();
	CreateBlock();
	UpdateIndicator();
}

void RunningState::OnPressUp()
{
	m_blockQueue.front()->Rotate(true);

	if ( TouchBound(m_blockQueue.front()) )
		m_blockQueue.front()->Rotate(false);

	UpdateIndicator();
}

void RunningState::OnPressEscape()
{
	m_gm->SetState(m_gm->GetPauseState());
}

void RunningState::SetInterval(unsigned int interval)
{
	if ( m_interval != interval)
	{
		m_interval = interval;
	}
}