#pragma once
#include "GameObject.h"
#include <string>
#include <SDL.h>
class Barrier :	public GameObject
{
private:
	bool deletable;
public:
	Barrier(SDL_Renderer* renderer, std::string fileName, int x, int y, int w, int h) : GameObject(renderer, fileName, x, y, w, h)
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
	~Barrier()
	{

	}
};