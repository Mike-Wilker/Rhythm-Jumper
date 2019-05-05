#pragma once
#include "Renderable.h"
class GameObject : public Renderable
{
protected:
	bool deletable;
public:
	GameObject(SDL_Renderer* renderer, int x, int y, int w, int h) : Renderable(renderer, x, y, w, h)
	{
		deletable = false;
	}
	virtual void update(int ticks) = 0;
	bool checkCollision(GameObject* other)
	{
		return (!deletable && this->location->checkCollision(other->location));
	}
	bool isDeletable()
	{
		return deletable;
	}
	~GameObject()
	{

	}
};