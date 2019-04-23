#include "stdafx.h"
#include <cstdlib>
#include <SDL.h>
#include <SDL_thread.h>
#include <stdio.h>
#include <iostream>
#include "Renderer.h"
#include "Midi-Interpreter.h"
#include "Player.h"
int draw(void* ptr);
int game(void* ptr);
std::vector<GameObject*> gameObjects;
int main(int argc, char* args[]) 
{
	gameObjects.emplace_back(new Player("resources\placeholder.bmp", 0, 700, 100, 100));
	SDL_Thread* drawThread = SDL_CreateThread(draw, NULL, NULL);
	SDL_Thread* gameThread = SDL_CreateThread(game, NULL, NULL);
	SDL_WaitThread(gameThread, NULL);
	return 0;
}
int draw(void* ptr)
{
	Renderer* renderer = new Renderer();
	while (true)
	{
		renderer->renderAll(gameObjects);
	}
	return 0;
}
int game(void* ptr)
{
	while (true)
	{
		for (int x = 0; x < gameObjects.size(); x++)
		{
			gameObjects.at(x)->update();
		}
	}
	return 0;
}