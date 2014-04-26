#include "Animation.h"
#include "Base.h"

#include <Windows.h>
#include <algorithm>

#include "Base.h"

BlockAnimation::BlockAnimation(Renderer* renderer)
: Animation(renderer)
, m_lastTickcount(GetTickCount())
, m_start(true)
{
	for ( int i = 0; i < 20; i++ )
	{
		Block* block = Block::CreateBlock(m_renderer, Point(std::rand()%WindowWidth, std::rand()%WindowHeight));;
		m_blockList.push_back(block);
	}

	InitBlockSpeed();
}

void BlockAnimation::InitBlockSpeed()
{
	BlockList::iterator it = m_blockList.begin();

	while ( it != m_blockList.end() )
	{
		//(*it)->Rotate(true);
		int x = std::rand() % 21 - 10;
		int y = std::rand() % 21 - 10;
		(*it)->SetSpeed(Point(x, y));
		++it;
	}
}

BlockAnimation::~BlockAnimation()
{
	BlockList::iterator it = m_blockList.begin();

	while ( it != m_blockList.end() )
	{
		delete (*it);
		++it;
	}
}

void BlockAnimation::Draw()
{
	if ( m_start && OnFrameChange() )
		OnAnimationStep();

	BlockList::iterator it = m_blockList.begin();

	while ( it != m_blockList.end() )
	{
		(*it)->Draw();
		++it;
	}
}

bool BlockAnimation::OnFrameChange()
{
	if ( GetTickCount() - m_lastTickcount > 16 )
	{
		m_lastTickcount = GetTickCount();
		return true;
	}

	return false;
}

void BlockAnimation::OnAnimationStep()
{
	BlockList::iterator it = m_blockList.begin();

	while ( it != m_blockList.end() )
	{
		Block* block = *it;
		Point speed(block->GetSpeed());

		Rect boundingRect(GetBlockBoundingRect(block));

		if ( boundingRect.x < 0 )
			speed.x = abs(speed.x);

		if ( boundingRect.x + boundingRect.w > WindowWidth )
			speed.x = -abs(speed.x);

		if ( boundingRect.y < 0 )
			speed.y = abs(speed.y);

		if ( boundingRect.y + boundingRect.h > WindowHeight )
			speed.y = -abs(speed.y);

		(*it)->SetSpeed(speed);
		(*it)->Move(speed);
		++it;
	}
}

Rect BlockAnimation::GetBlockBoundingRect(Block* block)
{
	const BlockUnit* unit = block->GetFirstBlock();

	int top = unit->y;
	int left = unit->x;
	int right = unit->x + unit->w;
	int bottom = unit->y + unit->h;

	while ( NULL != unit )
	{
		int ctop = unit->y;
		int cleft = unit->x;
		int cright = unit->x + unit->w;
		int cbottom = unit->y + unit->h;

		top = ctop < top ? ctop : top;
		left = cleft < left ? cleft : left;
		right = cright > right ? cright : right;
		bottom = cbottom > bottom ? cbottom : bottom;
		unit = block->GetNextBlock();
	}

	return Rect(left, top, right-left, bottom-top);
}