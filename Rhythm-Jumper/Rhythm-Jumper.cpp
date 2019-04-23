#include "stdafx.h"
#include <cstdlib>
#include <SDL.h>
#include <SDL_thread.h>
#include <stdio.h>
#include <iostream>
#include "Renderer.h"
#include "Midi-Interpreter.h"
#include "GameObject.h"
int draw(void* ptr);
int game(void* ptr);
std::vector<GameObject> gameObjects;
int main(int argc, char* args[]) 
{
	gameObjects.emplace_back(GameObject("resources\placeholder.bmp", 0, 700, 100, 100));
	SDL_Thread* drawThread = SDL_CreateThread(draw, NULL, NULL);
	SDL_Thread* gameThread = SDL_CreateThread(game, NULL, NULL);
	SDL_Delay(5000);
	return 0;
}
int draw(void* ptr)
{
	Renderer* renderer = new Renderer();
	while (true)
	{
		std::cout << "This is ";
		renderer->renderAll(gameObjects);
	}
	return 0;
}
int game(void* ptr)
{
	while (true)
	{
		std::cout << "a multithreaded application!\n";
		gameObjects.at(0).location->x++;
		SDL_Delay(1);
	}
	return 0;
}