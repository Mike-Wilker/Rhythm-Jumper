#pragma once
#include "GameObject.h"
#include <string>
#include <SDL.h>
class Barrier : public GameObject
{
	bool canScore;
public:
	Barrier(SDL_Renderer* renderer, int x, int y, int w, int h) : GameObject(renderer, x, y, w, h)
	{
		deletable = false;
		canScore = true;
	}
	void hit()
	{
		deletable = true;
		canScore = false;
	}
	bool isDeletable()
	{
		return deletable;
	}
	bool tryScore()
	{
		if (canScore)
		{
			canScore = false;
			return true;
		}
		else
		{
			return false;
		}
	}
	virtual void update(int ticks) = 0;
	~Barrier()
	{

	}
};