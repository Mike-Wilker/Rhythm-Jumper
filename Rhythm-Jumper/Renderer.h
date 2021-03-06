#pragma once
#include <list>
#include "Renderable.h"
#include "Barrier.h"
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
			fprintf(stderr, "Could not initialize sdl2: %s\n", SDL_GetError());
			return;
		}
		window = SDL_CreateWindow("Rhythm-Jumper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
			return;
		}
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL)
		{
			fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
			return;
		}
	}
	void renderAll(std::list<Barrier*> barriers, Renderable* player, std::list<HudElement*> hudElements)
	{
		SDL_SetRenderDrawColor(renderer, 0x11, 0x11, 0x11, 0x11);
		SDL_RenderClear(renderer);
		for (Renderable* renderable : barriers)
		{
			if (renderable != nullptr)
			{
				renderable->render(SDL_GetWindowSurface(window), renderer);
			}
		}
		if (player != nullptr)
		{
			player->render(SDL_GetWindowSurface(window), renderer);
		}
		for (HudElement* hudElement : hudElements)
		{
			hudElement->render(renderer);
		}
		SDL_RenderPresent(renderer);
	}
	SDL_Window* getWindow()
	{
		return window;
	}
	SDL_Renderer* getRenderer()
	{
		return renderer;
	}
	~Renderer()
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
	}
};