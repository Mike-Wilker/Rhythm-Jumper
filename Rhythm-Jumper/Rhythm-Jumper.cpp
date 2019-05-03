#include "stdafx.h"
#include <cstdlib>
#include <SDL.h>
#include <SDL_thread.h>
#include "Clock.h"
#include <stdio.h>
#include <iostream>
#include "Renderer.h"
#include "Midi-Interpreter.h"
#include "Player.h"
#include "Fence.h"
int initializePlayerThread(void* ptr);
int initializeInputThread(void* ptr);
int initializeGameThread(void* ptr);
int initializeDrawThread(void* ptr);
Player* player = nullptr;
std::vector<Barrier*> barriers;
Renderer* renderer = nullptr;
KeyHandler* keyHandler = nullptr;
constexpr int minFrameTime = 8; /* Sets the maximum framerate to 125 fps. */
int main(int argc, char* args[])
{
	renderer = new Renderer();
	keyHandler = new KeyHandler();
	player = new Player(renderer->getRenderer(), 0, 700, 100, 100);
	barriers.emplace_back(new Fence(renderer->getRenderer(), 700, 700, 100, 100));
	SDL_Thread* playerThread = SDL_CreateThread(initializePlayerThread, NULL, NULL);
	SDL_Thread* inputThread = SDL_CreateThread(initializeInputThread, NULL, NULL);
	SDL_Thread* gameThread = SDL_CreateThread(initializeGameThread, NULL, NULL);
	SDL_Thread* drawThread = SDL_CreateThread(initializeDrawThread, NULL, NULL);
	SDL_WaitThread(gameThread, NULL);
	return 0;
}
int initializePlayerThread(void* ptr)
{
	Clock* playerThreadClock = new Clock();
	while (true)
	{
		int timePassed = playerThreadClock->getTimePassed();
		player->update(barriers, timePassed);
		int tickTime = playerThreadClock->getTimePassed();
		if (minFrameTime > (tickTime + timePassed))
		{
			SDL_Delay(minFrameTime - (tickTime + timePassed));
		}
	}
	return 0;
}
int initializeInputThread(void* ptr)
{
	while (true)
	{
		keyHandler->pollKeys();
	}
	return 0;
}
int initializeGameThread(void* ptr)
{
	Clock* gameThreadClock = new Clock();
	while (true)
	{
		int timePassed = gameThreadClock->getTimePassed();
		for (int x = 0; x < barriers.size(); x++)
		{
			barriers.at(x)->update(timePassed);
		}
		int tickTime = gameThreadClock->getTimePassed();
		if (minFrameTime > (tickTime + timePassed))
		{
			SDL_Delay(minFrameTime - (tickTime + timePassed));
		}
	}
	return 0;
}
int initializeDrawThread(void* ptr)
{
	Clock* drawThreadClock = new Clock();
	while (true)
	{
		renderer->renderAll(barriers, player);
		double frameTime = 1000.0 / drawThreadClock->getTimePassed();
		if (minFrameTime > frameTime)
		{
			SDL_Delay(minFrameTime - frameTime);
		}
	}
	return 0;
}
