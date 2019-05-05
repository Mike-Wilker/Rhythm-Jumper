#pragma once
class Clock
{
	int lastTime;
public:
	Clock()
	{
		lastTime = SDL_GetTicks();
	}
	int getTimePassedNoReset()
	{
		return SDL_GetTicks() - lastTime;
	}
	int getTimePassed()
	{
		int timeElapsed = SDL_GetTicks() - lastTime;
		lastTime = SDL_GetTicks();
		return timeElapsed;
	}
	~Clock()
	{

	}
};