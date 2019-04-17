#include "stdafx.h"
#include <cstdlib>
#include <SDL.h>
#include <SDL_thread.h>
#include <stdio.h>
#include <iostream>
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
int draw(void* ptr);
int game(void* ptr);
int draw(void* ptr)
{
	while (true)
	{
		std::cout << "This thread functions.";
		SDL_Delay(rand() % 100);
	}
	return 0;
}
int game(void* ptr)
{
	while (true)
	{
		std::cout << "GameThread";
		SDL_Delay(rand() % 100);
	}
	return 0;
}
int main(int argc, char* args[]) 
{
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
	{
		fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
		return 1;
	}
	window = SDL_CreateWindow(
		"Rhythm-Jumper",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);
	if (window == NULL)
	{
		fprintf(stderr, "could not create window: %s\n", SDL_GetError());
		return 1;
	}
	SDL_Thread* drawThread = SDL_CreateThread(draw, NULL, NULL);
	SDL_Thread* gameThread = SDL_CreateThread(game, NULL, NULL);
	screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
	SDL_UpdateWindowSurface(window);
	SDL_Delay(2000);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}