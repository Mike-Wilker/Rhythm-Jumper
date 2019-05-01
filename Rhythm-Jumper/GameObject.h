#pragma once
#include "Renderable.h"
class GameObject : public Renderable
{
public:
	GameObject(SDL_Renderer* renderer, std::string fileName, int x, int y, int w, int h) : Renderable(renderer, fileName, x, y, w, h)
	{
		
	}
	virtual void update(int ticks) = 0;
	bool checkCollision(GameObject* other)
	{
		return SDL_HasIntersection(this->location, other->location);
	}
	~GameObject()
	{

	}
};