#pragma once
#include <vector>
#include "Renderable.h"
#include "GameObject.h"
constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = 1080;
class Renderer
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
public:
	Renderer()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
			return;
		}
		window = SDL_CreateWindow("Rhythm-Jumper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			fprintf(stderr, "could not create window: %s\n", SDL_GetError());
			return;
		}
		renderer = SDL_CreateRenderer(window, -1, NULL);
	}
	void renderAll(std::vector<GameObject*> pipeline)
	{
		SDL_FillRect(SDL_GetWindowSurface(window), NULL, SDL_MapRGB(SDL_GetWindowSurface(window)->format, 0x00, 0x00, 0x00));
		for (Renderable* renderable : pipeline)
		{
			renderable->render(SDL_GetWindowSurface(window), renderer);
		}
		SDL_UpdateWindowSurface(window);
	}
	~Renderer()
	{
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
};