
#include "SDLRenderer.h"
#include "Utils.h"
#include "entity/Block.h"
#include <algorithm>

Block::Block(const Block& block)
	: GameObject(block.m_renderer)
{
	BlockList::const_iterator it = block.m_blockList.begin();

	while ( it != block.m_blockList.end() )
	{
		BlockUnit* unit = new BlockUnit(**it);
		AddRect(unit);
		++it;
	}
	
	m_center = block.m_center;
}

Block* Block::CreateBlock(Renderer* renderer, const Point& topLeft)
{
	Block* block = NULL;

	BlockType type = (BlockType)(std::rand() % 7);

	switch ( type )
	{
	case TBLOCK:
		block = CreateTBlock(renderer);
		break;
	case LBLOCK:
		block = CreateLBlock(renderer);
		break;
	case JBLOCK:
		block = CreateJBlock(renderer);
		break;
	case SQUAREBLOCK:
		block = CreateSquareBlock(renderer);
		break;
	case ZBLOCK:
		block = CreateZBlock(renderer);
		break;
	case IBLOCK:
		block = CreateIBlock(renderer);
		break;
	case SBLOCK:
		block = CreateSBlock(renderer);
		break;
	}

	block->m_type = type;
	block->SetRandomColor();
	block->Move(topLeft);

	return block;
}

Block* Block::CreateIBlock(Renderer* renderer)
{
	Block* block = new Block(renderer);
	block->AddRect(new BlockUnit(0, 0));
	block->AddRect(new BlockUnit(0, BlockUnitHeight));
	block->AddRect(new BlockUnit(0, BlockUnitHeight*2));
	block->AddRect(new BlockUnit(0, BlockUnitHeight*3));

	block->m_center = Point(BlockUnitWidth, BlockUnitHeight*2);

	return block;
}

Block* Block::CreateJBlock(Renderer* renderer)
{
	Block* block = new Block(renderer);
	block->AddRect(new BlockUnit(BlockUnitWidth, 0));
	block->AddRect(new BlockUnit(BlockUnitWidth, BlockUnitHeight));
	block->AddRect(new BlockUnit(BlockUnitWidth, BlockUnitHeight*2));
	block->AddRect(new BlockUnit(0, BlockUnitHeight*2));

	block->m_center = Point(BlockUnitWidth*1.5, BlockUnitHeight*1.5);

	return block;
}

Block* Block::CreateLBlock(Renderer* renderer)
{
	Block* block = new Block(renderer);
	block->AddRect(new BlockUnit(0, 0));
	block->AddRect(new BlockUnit(0, BlockUnitHeight));
	block->AddRect(new BlockUnit(0, BlockUnitHeight*2));
	block->AddRect(new BlockUnit(BlockUnitWidth, BlockUnitHeight*2));

	block->m_center = Point(BlockUnitWidth*0.5, BlockUnitHeight*1.5);

	return block;
}

Block* Block::CreateSquareBlock(Renderer* renderer)
{
	Block* block = new Block(renderer);
	block->AddRect(new BlockUnit(0, 0));
	block->AddRect(new BlockUnit(0, BlockUnitHeight));
	block->AddRect(new BlockUnit(BlockUnitWidth, 0));
	block->AddRect(new BlockUnit(BlockUnitWidth, BlockUnitHeight));

	block->m_center = Point(BlockUnitWidth, BlockUnitHeight);

	return block;
}

Block* Block::CreateSBlock(Renderer* renderer)
{
	Block* block = new Block(renderer);
	block->AddRect(new BlockUnit(BlockUnitWidth, 0));
	block->AddRect(new BlockUnit(BlockUnitWidth*2, 0));
	block->AddRect(new BlockUnit(0, BlockUnitHeight));
	block->AddRect(new BlockUnit(BlockUnitWidth, BlockUnitHeight));

	block->m_center = Point(BlockUnitWidth*1.5, BlockUnitHeight*1.5);

	return block;
}

Block* Block::CreateZBlock(Renderer* renderer)
{
	Block* block = new Block(renderer);
	block->AddRect(new BlockUnit(0, 0));
	block->AddRect(new BlockUnit(BlockUnitWidth, 0));
	block->AddRect(new BlockUnit(BlockUnitWidth, BlockUnitHeight));
	block->AddRect(new BlockUnit(BlockUnitWidth*2, BlockUnitHeight));

	block->m_center = Point(BlockUnitWidth*1.5, BlockUnitHeight*1.5);

	return block;
}

Block* Block::CreateTBlock(Renderer* renderer)
{
	Block* block = new Block(renderer);
	block->AddRect(new BlockUnit(0, 0));
	block->AddRect(new BlockUnit(BlockUnitWidth, 0));
	block->AddRect(new BlockUnit(BlockUnitWidth*2, 0));
	block->AddRect(new BlockUnit(BlockUnitWidth, BlockUnitHeight));

	block->m_center = Point(BlockUnitWidth*1.5, BlockUnitHeight*0.5);

	return block;
}

void Block::AddRect(BlockUnit* rect)
{
	m_blockList.push_back(rect);
}

void Block::SetRandomColor()
{
	Color color(ColorGroup[std::rand() % ColorCount]);

	BlockList::iterator it = m_blockList.begin();

	while ( it != m_blockList.end() )
	{
		(*it)->color = color;
		++it;
	}
}

void Block::MoveLeft()
{
	BlockList::iterator it = m_blockList.begin();

	while ( it != m_blockList.end() )
	{
		(*it)->x -= BlockUnitWidth;
		++it;
	}

	m_center.x -= BlockUnitWidth;
}

void Block::MoveUp()
{
	BlockList::iterator it = m_blockList.begin();

	while ( it != m_blockList.end() )
	{
		(*it)->y -= BlockUnitHeight;
		++it;
	}

	m_center.y -= BlockUnitHeight;
}

void Block::MoveRight()
{
	BlockList::iterator it = m_blockList.begin();

	while ( it != m_blockList.end() )
	{
		(*it)->x += BlockUnitWidth;
		++it;
	}

	m_center.x += BlockUnitWidth;
}

void Block::MoveDown()
{
	BlockList::iterator it = m_blockList.begin();

	while ( it != m_blockList.end() )
	{
		(*it)->y += BlockUnitHeight;
		++it;
	}

	m_center.y += BlockUnitHeight;
}

void Block::Move(int xUnit, int yUnit)
{
	BlockList::iterator it = m_blockList.begin();

	while ( it != m_blockList.end() )
	{
		(*it)->x += xUnit * BlockUnitWidth;
		(*it)->y += yUnit * BlockUnitHeight;
		++it;
	}

	m_center.x += xUnit * BlockUnitWidth;
	m_center.y += yUnit * BlockUnitHeight;
}

void Block::Move(const Point& point)
{
	BlockList::iterator it = m_blockList.begin();

	while ( it != m_blockList.end() )
	{
		(*it)->x += point.x;
		(*it)->y += point.y;
		++it;
	}

	m_center = m_center + point;
}

void Block::Rotate(bool clockwize)
{
	BlockList::iterator it = m_blockList.begin();

	while ( it != m_blockList.end() )
	{
		::Rotate(**it, m_center, clockwize);
		++it;
	}
}

void Block::Draw()
{
	BlockList::iterator it = m_blockList.begin();

	while ( it != m_blockList.end() )
	{
		m_renderer->FillRect(**it, (*it)->color);
		m_renderer->DrawRect(**it, ColorPoolsBackground);
		++it;
	}
}

void Block::SetSpeed(const Point& speed)
{
	m_speed = speed;
}

const Point& Block::GetSpeed()
{
	return m_speed;
}

const BlockUnit* Block::GetFirstBlock()
{
	m_itToBlockList = m_blockList.begin();
	return (*m_itToBlockList);
}

const BlockUnit* Block::GetNextBlock()
{
	return (++m_itToBlockList == m_blockList.end() ? NULL : (*m_itToBlockList));
}

void Block::Copy(Block* block)
{
	BlockList::iterator it = m_blockList.begin();
	const BlockUnit* itr = block->GetFirstBlock();

	while ( it != m_blockList.end() )
	{
		(*it)->Copy(itr);
		itr = block->GetNextBlock();
		++it;
	}

	m_center = block->m_center;
}

void Block::SetOpacity(int alpha)
{
	BlockList::iterator it = m_blockList.begin();

	while ( it != m_blockList.end() )
	{
		(*it)->GetColor().a = alpha;
		++it;
	}
}

Block::~Block()
{
	BlockList::iterator it = m_blockList.begin();

	while ( it != m_blockList.end() )
	{
		delete *it;
		++it;
	}
}
