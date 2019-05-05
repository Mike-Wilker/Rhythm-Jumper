#include "stdafx.h"
#include <list>
#include <SDL.h>
#include <assert.h>
#include "Clock.h"
#include "KeyHandler.h"
#include "Renderable.h"
#include "GameObject.h"
#include "Barrier.h"
#include "Fence.h"
#include "Player.h"
#include "Renderer.h"
#include "MidiInterpreter.h"
int initializePlayerThread(void* ptr);
int initializeGameThread(void* ptr);
int initializeDrawThread(void* ptr);
Player* player = nullptr;
std::list<Barrier*> barriers;
Renderer* renderer = nullptr;
KeyHandler* keyHandler = nullptr;
constexpr int minFrameTime = 8;
int main(int argc, char* args[])
{
	renderer = new Renderer();
	keyHandler = new KeyHandler();
	SDL_Thread* drawThread = SDL_CreateThread(initializeDrawThread, NULL, NULL);
	SDL_Thread* playerThread = SDL_CreateThread(initializePlayerThread, NULL, NULL);
	SDL_Thread* gameThread = SDL_CreateThread(initializeGameThread, NULL, NULL);
	Clock* inputThreadPollingClock = new Clock();
	while (true)
	{
		keyHandler->pollKeys();
		int tickTime = inputThreadPollingClock->getTimePassed();
		if (tickTime < minFrameTime)
		{
			SDL_Delay(minFrameTime - tickTime);
		}
	}
	return 0;
}
int initializePlayerThread(void* ptr)
{
	Clock* playerThreadClock = new Clock();
	player = new Player(renderer->getRenderer());
	while (true)
	{
		int timePassed = playerThreadClock->getTimePassed();
		player->update(barriers, keyHandler, timePassed);
		int tickTime = playerThreadClock->getTimePassed();
		if (minFrameTime > (tickTime + timePassed))
		{
			SDL_Delay(minFrameTime - (tickTime + timePassed));
		}
	}
	return 0;
}
int initializeGameThread(void* ptr)
{
	Clock* gameThreadClock = new Clock();
	barriers.emplace_front(new Fence(renderer->getRenderer(), 1000));
	while (true)
	{
		int timePassed = gameThreadClock->getTimePassed();
		for (Barrier* barrier : barriers)
		{
			barrier->update(timePassed);
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
		int tickTime = drawThreadClock->getTimePassed();
		if (minFrameTime > tickTime)
		{
			SDL_Delay(minFrameTime - tickTime);
		}
	}
	return 0;
}