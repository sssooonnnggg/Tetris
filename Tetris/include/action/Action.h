/*!
	Description : Define an "action" which is associated with GameUI. 
	Author		: Ruining Song
	Date		: 2014/04/26
*/

#ifndef ACTION_H
#define ACTION_H

class Action
{
public:
	virtual void operator()() = 0;
};

class GameManager;
class StartAction : public Action
{
public:
	StartAction(GameManager* gm);
	void operator()();

private:
	GameManager* m_gm;
};

class ResumeAction : public Action
{
public:
	ResumeAction(GameManager* gm);
	void operator()();

private:
	GameManager* m_gm;
};

class MainMenuAction : public Action
{
public:
	MainMenuAction(GameManager* gm);
	void operator()();

private:
	GameManager* m_gm;
};

#endif // ACTION_H