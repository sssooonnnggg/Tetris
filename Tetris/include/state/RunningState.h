/*!
	Description : Brief the state "running" of the game.
	Author		: Ruining Song
	Date		: 2014/04/15
*/

#ifndef RUNNINGSTATE_H
#define RUNNINGSTATE_H

#include "GameState.h"

#include <list>

class Block;
class Pools;
class Score;

class UIManager;
class Label;

class RunningState : public GameState
{
public:
	RunningState(GameManager* gm, Renderer* renderer, unsigned int interval = 1000);
	~RunningState();

	void Init();
	std::wstring Name();
	void Draw();
	void Update();

	void Notify(Event* e);
	void Reset();

private:
	void CreateScoreUI();
	void CreateBlock();
	void CreatePools();
	void CreateScore();
	void InitBlockQueue();

	void OnPressLeft();
	void OnPressRight();
	void OnPressDown();
	void OnReleaseDown();
	void OnPressSpace();
	void OnPressUp();
	void OnPressEscape();

	bool FrameChange();
	void MoveBlockDown();
	void UpdatePools();
	void UpdateIndicator();
	void UpdateScore();
	bool TouchBound(Block* block);
	void SetSoftDrop(bool onSoftdrop);
	void SetInterval(unsigned int interval);

private:
	unsigned int m_interval;
	unsigned int m_softdropInterval;
	bool m_onSoftdrop;
	unsigned int m_lastTickcount;

	Point m_topLeft;

	typedef std::list<Block*> BlockQueue;
	BlockQueue m_blockQueue;
	Block* m_indicator;
	Pools* m_pools;

	/*!
	\brief
		Internal class used for logging current scroe info.
	*/
	class ScroInfo
	{
	public:
		ScroInfo()
			: m_score(0), m_level(1), m_line(0)
		{

		}

		int m_score;
		int m_level;
		int m_line;
	};
	
	ScroInfo m_scroInfo;
	UIManager* m_scoreUI;
	Label* m_levelText;
	Label* m_scoreText;
	Label* m_lineText;
};

#endif // RUNNINGSTATE_H