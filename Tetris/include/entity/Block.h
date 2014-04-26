/*!
	Description : Brief the block's entity.
	Author		: Ruining Song
	Date		: 2014/04/26
*/
#ifndef BLOCK_H
#define BLOCK_H

#include "entity/GameObject.h"

class Block : public GameObject
{
public:

	Block::Block(const Block& block);

	static Block* CreateBlock(Renderer* renderer, const Point& topLeft);

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void Move(int xUnit, int yUnit);
	void Move(const Point& point);
	void Rotate(bool clockwize);

	void Draw();

	void SetSpeed(const Point& speed);
	const Point& GetSpeed();

	const BlockUnit* GetFirstBlock();
	const BlockUnit* GetNextBlock();

	void Copy(Block* block);
	void SetOpacity(int alpha);

	~Block();

private:
	Block(Renderer* renderer)
		: GameObject(renderer)
		, m_center(0, 0)
		, m_speed(0, 0)
	{}

	enum BlockType { TBLOCK, LBLOCK, JBLOCK, SQUAREBLOCK, ZBLOCK, IBLOCK, SBLOCK};
	static Block* CreateTBlock(Renderer* renderer);
	static Block* CreateLBlock(Renderer* renderer);
	static Block* CreateJBlock(Renderer* renderer);
	static Block* CreateSquareBlock(Renderer* renderer);
	static Block* CreateZBlock(Renderer* renderer);
	static Block* CreateIBlock(Renderer* renderer);
	static Block* CreateSBlock(Renderer* renderer);

	void AddRect(BlockUnit* rect);
	void SetRandomColor();

private:
	typedef std::list<BlockUnit*> BlockList;
	BlockList m_blockList;
	BlockType m_type;
	Point m_center;		// rotate around this point
	Point m_speed;					// used by block animation
	BlockList::iterator m_itToBlockList;
};

#endif // BLOCK_H