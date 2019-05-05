#pragma once
#include "GameObject.h"
#include <string>
#include <SDL.h>
class Barrier : public GameObject
{
public:
	Barrier(SDL_Renderer* renderer, int x, int y, int w, int h) : GameObject(renderer, x, y, w, h)
	{
		deletable = false;
	}
	void hit()
	{
		deletable = true;
	}
	bool isDeletable()
	{
		return deletable;
	}
	virtual void update(int ticks) = 0;
	~Barrier()
	{

	}
};