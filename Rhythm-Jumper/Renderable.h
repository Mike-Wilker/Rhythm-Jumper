#pragma once
class Renderable
{
public:
	SDL_Surface* sprite = nullptr;
	SDL_Rect* location = nullptr;
	Renderable(std::string fileName, int x, int y, int w, int h)
	{
		sprite = SDL_LoadBMP(fileName.c_str());
		location = new SDL_Rect();
		location->x = x;
		location->y = y;
		location->w = h;
		location->h = h;
	}
	void render(SDL_Surface* window)
	{
		SDL_FillRect(window, location, SDL_MapRGB(window->format, 0xFF, 0x00, 0x00));
		SDL_BlitSurface(sprite, location, window, NULL);
	}
	~Renderable()
	{
		SDL_FreeSurface(sprite);
		delete sprite;
	}
};