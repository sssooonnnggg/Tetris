/*!
	Description : Block animation
	Autrhor		: Ruining Song
	Date		: 2014/3/14
*/

#ifndef ANIMATION_H
#define ANIMATION_H

#include <list>

#include "entity/Block.h"

class GameObject;
class Block;

class Animation : public GameObject
{
public:
	Animation(Renderer* renderer)
		: GameObject(renderer)
	{}

	virtual void Draw() = 0;
};

class BlockAnimation : public Animation
{
public:
	BlockAnimation(Renderer* renderer);
	~BlockAnimation();

	void Draw();

private:
	void InitBlockSpeed();
	bool OnFrameChange();
	void OnAnimationStep();
	Rect GetBlockBoundingRect(Block* block);

private:
	typedef std::list<Block*> BlockList;
	BlockList m_blockList;
	unsigned int m_lastTickcount;
	bool m_start;
};


#endif // ANIMATION_H