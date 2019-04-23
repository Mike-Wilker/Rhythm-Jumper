#pragma once
#include "Renderable.h"
class GameObject : public Renderable
{
public:
	GameObject(std::string fileName, int x, int y, int w, int h) : Renderable(fileName, x, y, w, h)
	{
		
	}
	void update()
	{

	}
	~GameObject()
	{

	}
};