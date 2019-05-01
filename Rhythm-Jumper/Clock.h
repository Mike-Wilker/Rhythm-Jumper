#pragma once
#include <SDL.h>
class Clock
{
	int lastTime;
public:
	Clock()
	{
		lastTime = SDL_GetTicks();
	}
	int getTimeAllotted()
	{
		return (lastTime = SDL_GetTicks()) - lastTime;
	}
	~Clock()
	{

	}
};