/*!
	Description : Brief the pools entity.
	Author		: Ruining Song
	Date		: 2014/04/26
*/
#ifndef POOLS_H
#define POOLS_H

#include "entity/GameObject.h"

class Pools : public GameObject
{
public:
	Pools(Renderer* renderer, const Point& topLeft, int xCount, int yCount);
	~Pools();

	void Draw();

	bool IsFilled(int row, int column);
	void SetFilled(int row, int column, const Color& color);

	/*!
	\brief
		Return cleared row count.
	*/
	int Clear();
	bool IsFilled(int row);
	void MoveDown(int row, int step);

	bool IsFullFilled();

	void Reset();

private:
	void InitPools(const Point& topLeft);
	BlockUnit* UnitAt(int x, int y);

private:
	BlockUnit* m_pools;
	int m_xCount;
	int m_yCount;
	Point m_topLeft;
};

#endif // POOLS_H