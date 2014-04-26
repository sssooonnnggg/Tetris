/*!
	Description : Game object
	Author		: Ruinning Song
	Date		: 2014/3/8
*/

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <list>
#include <string>
#include "Base.h"

class Renderer;

class GameObject
{
public:
	GameObject(Renderer* renderer)
		: m_renderer(renderer)
	{}

	virtual void Draw() = 0;

protected:
	Renderer* m_renderer;
};

#endif // GAMEOBJECT_H