#pragma once
#include <vector>
class Renderer
{
	class Renderable
	{
		SDL_Surface* sprite = nullptr;
		SDL_Rect* location = nullptr;
		Renderable(std::string fileName, int x, int y, int w, int h)
		{
			sprite = SDL_LoadBMP(fileName.c_str());
			location->x = x;
			location->y = y;
			location->w = h;
			location->h = h;
		}
		void render(SDL_Surface* window)
		{
			SDL_BlitSurface(window, NULL, sprite, location);
		}
	};
	std::vector<Renderable>* pipeline = new std::vector<Renderable>();

};