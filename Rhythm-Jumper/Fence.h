#pragma once
#include "Barrier.h"
class Fence : public Barrier
{
public:
	Fence(SDL_Renderer* renderer, std::string fileName, int x, int y, int w, int h) : Barrier(renderer, fileName, x, y, w, h)
	{

	}
	~Fence()
	{

	}
};