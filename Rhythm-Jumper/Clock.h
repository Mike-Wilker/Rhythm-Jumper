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
	int getTimePassed()
	{
		return (lastTime = SDL_GetTicks()) - lastTime;
	}
	~Clock()
	{

	}
};