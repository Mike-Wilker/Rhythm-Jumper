#include "stdafx.h"
#include <list>
#include <SDL.h>
#include <iostream>
#include <assert.h>
#include "Clock.h"
#include "KeyHandler.h"
#include "Rectangle.h"
#include "HudElement.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Player.h"
#include "Bar.h"
#include "Healthbar.h"
#include "Barrier.h"
#include "Fence.h"
#include "Renderable.h"
#include "MidiInterpreter.h"
int initializePlayerThread(void* ptr);
int initializeGameThread(void* ptr);
int initializeDrawThread(void* ptr);
bool isRemovable(Barrier* value);
Player* player = nullptr;
std::list<Barrier*> barriers;
Renderer* renderer = nullptr;
KeyHandler* keyHandler = nullptr;
std::list<HudElement*> hudElements;
constexpr int minFrameTime = 8;
int main(int argc, char* args[])
{
	renderer = new Renderer();
	keyHandler = new KeyHandler();
	player = new Player(renderer->getRenderer());
	hudElements.emplace_front(new HealthBar(player));
	for (int x = 0; x < 100; x++)
	{
		barriers.emplace_front(new Fence(renderer->getRenderer(), (1000 * (x + 1)) + rand() % 500));
	}
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
	
	while (true)
	{
		int timePassed = playerThreadClock->getTimePassed();
		player->update(barriers, keyHandler, timePassed);
		int tickTime = playerThreadClock->getTimePassed();
		if (minFrameTime > (tickTime + timePassed))
		{
			SDL_Delay(minFrameTime - (tickTime + timePassed));
		}
		if (player->getHealth() <= 0.0)
		{
		}
	}
	return 0;
}
int initializeGameThread(void* ptr)
{
	Clock* gameThreadClock = new Clock();
	while (true)
	{
		int timePassed = gameThreadClock->getTimePassed();
		barriers.remove_if(isRemovable);
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
		renderer->renderAll(barriers, player, hudElements);
		int tickTime = drawThreadClock->getTimePassed();
		if (minFrameTime > tickTime)
		{
			SDL_Delay(minFrameTime - tickTime);
		}
	}
	return 0;
}
bool isRemovable(Barrier* value)
{
	return value->isDeletable();
}