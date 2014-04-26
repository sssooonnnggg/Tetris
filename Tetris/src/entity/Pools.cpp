#include "entity/Pools.h"
#include "SDLRenderer.h"

Pools::Pools(Renderer* renderer, const Point& topLeft, int xCount, int yCount)
: GameObject(renderer)
, m_xCount(xCount)
, m_yCount(yCount)
, m_pools(NULL)
, m_topLeft(topLeft)
{
	m_pools = new BlockUnit[xCount * yCount];
	InitPools(topLeft);
}

Pools::~Pools()
{
	delete [] m_pools;
}

void Pools::InitPools(const Point& topLeft)
{
	for ( int i = 0; i < m_xCount; ++i )
	{
		for ( int j = 0; j < m_yCount; ++j )
		{
			BlockUnit* curUnit = UnitAt(i, j);
			curUnit->x = topLeft.x + i * BlockUnitWidth;
			curUnit->y = topLeft.y + j * BlockUnitHeight;
			curUnit->w = BlockUnitWidth;
			curUnit->h = BlockUnitHeight;
		}
	}
}

BlockUnit* Pools::UnitAt(int x, int y)
{
	if ( x >= m_xCount 
		|| x < 0
		|| y >= m_yCount
		|| y < 0 )
		return NULL;

	return m_pools + m_xCount * y + x;
}

void Pools::Draw()
{
	// Draw Background
	m_renderer->FillRect(
		Rect(m_topLeft.x, m_topLeft.y, m_xCount*BlockUnitWidth, m_yCount*BlockUnitHeight), Color(200, 200, 200));

	// Draw grid
	for ( int i = 0; i < m_xCount; ++i )
	{
		m_renderer->DrawLine(
			m_topLeft + Point(i*BlockUnitWidth, 0), 
			m_topLeft + Point(i*BlockUnitWidth, m_yCount*BlockUnitHeight-1), 
			ColorPoolsBackground);
	}

	for ( int i = 0; i < m_yCount; ++i )
	{
		m_renderer->DrawLine(
			m_topLeft + Point(0, i*BlockUnitHeight),
			m_topLeft + Point(m_xCount*BlockUnitWidth-1, i*BlockUnitHeight),
			ColorPoolsBackground);
	}

	// Draw blocks
	for ( int i = 0; i < m_xCount; ++i )
	{
		for ( int j = 0; j < m_yCount; ++j )
		{
			BlockUnit* curUnit = UnitAt(i, j);

			if ( curUnit->fill )
			{
				m_renderer->FillRect(*curUnit, curUnit->color);
				m_renderer->DrawRect(*curUnit, ColorPoolsBackground);
			}
		}
	}
}

bool Pools::IsFilled(int row, int column)
{
	if ( NULL == UnitAt(column, row) || UnitAt(column, row)->fill )
		return true;

	return false;
}

void Pools::SetFilled(int row, int column, const Color& color)
{
	BlockUnit* unit = UnitAt(column, row);

	if ( NULL != unit )
	{
		unit->fill = true;
		unit->color = color;
	}
}

int Pools::Clear()
{
	int rowCleared = 0;

	for ( int row = m_yCount-1; row >= 0; row-- )
	{
		if ( IsFilled(row) )
			rowCleared++;
		else
			MoveDown(row, rowCleared);
	}

	return rowCleared;
}
bool Pools::IsFilled(int row)
{
	for ( int i = 0; i < m_xCount; ++i )
	{
		BlockUnit* curUnit = UnitAt(i, row);

		if ( !curUnit->fill )
			return false;
	}

	return true;
}

void Pools::MoveDown(int row, int step)
{
	if ( 0 == step ) return;

	for ( int i = 0; i < m_xCount; ++i )
	{
		BlockUnit* curUnit = UnitAt(i, row);
		BlockUnit* newCurUnit = UnitAt(i, row + step);
		newCurUnit->fill = curUnit->fill;
		newCurUnit->color = curUnit->color;
		curUnit->fill = false;
	}
}

bool Pools::IsFullFilled()
{
	for ( int i = 0; i < m_xCount; ++i )
	{
		BlockUnit* curUnit = UnitAt(i, 0);

		if ( curUnit->fill )
			return true;
	}

	return false;
}

void Pools::Reset()
{
	for ( int i = 0; i < m_xCount; ++i )
		for ( int j = 0; j < m_yCount; ++j )
			UnitAt(i, j)->fill = false;
}