#pragma once
class Renderable
{
public:
	SDL_Texture* sprite = nullptr;
	SDL_Rect* location = nullptr;
	Renderable(std::string fileName, int x, int y, int w, int h)
	{
		SDL_Surface* surface = SDL_LoadBMP(fileName.c_str());
		sprite = SDL_CreateTextureFromSurface(NULL, surface);
		SDL_FreeSurface(surface);
		std::cout << sprite;
		location = new SDL_Rect();
		location->x = x;
		location->y = y;
		location->w = h;
		location->h = h;
	}
	void render(SDL_Surface* window, SDL_Renderer* renderer)
	{
		SDL_FillRect(window, location, SDL_MapRGB(window->format, 0xFF, 0x00, 0x00));
		SDL_RenderCopy(renderer, sprite, NULL, location);
	}
	~Renderable()
	{
		SDL_DestroyTexture(sprite);
	}
};