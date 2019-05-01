#include "stdafx.h"
#include <cstdlib>
#include <SDL.h>
#include <SDL_thread.h>
#include <stdio.h>
#include <iostream>
#include "Renderer.h"
#include "Midi-Interpreter.h"
#include "Player.h"
int initializePlayerThread(void* ptr);
int initializeInputThread(void* ptr);
int initializeGameThread(void* ptr);
int initializeDrawThread(void* ptr);
Player* player = nullptr;
std::vector<Barrier*> barriers;
Renderer* renderer = nullptr;
KeyHandler* keyHandler = nullptr;
int main(int argc, char* args[])
{
	
	renderer = new Renderer();
	keyHandler = new KeyHandler();
	player = new Player(renderer->getRenderer(), "resources//placeholder.bmp", 0, 700, 100, 100);
	SDL_Thread* playerThread = SDL_CreateThread(initializePlayerThread, NULL, NULL);
	SDL_Thread* inputThread = SDL_CreateThread(initializeInputThread, NULL, NULL);
	SDL_Thread* gameThread = SDL_CreateThread(initializeGameThread, NULL, NULL);
	SDL_Thread* drawThread = SDL_CreateThread(initializeDrawThread, NULL, NULL);
	SDL_WaitThread(gameThread, NULL);
	return 0;
}
int initializePlayerThread(void* ptr)
{
	while (true)
	{
		player->update(barriers, SDL_GetTicks());
	}
}
int initializeDrawThread(void* ptr)
{
	while (true)
	{
		renderer->renderAll(barriers, player);
	}
	return 0;
}
int initializeGameThread(void* ptr)
{
	while (true)
	{
		for (int x = 0; x < barriers.size(); x++)
		{
			barriers.at(x)->update(SDL_GetTicks());
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
