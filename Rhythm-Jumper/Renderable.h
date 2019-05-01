#pragma once
class Renderable
{
public:
	SDL_Rect* location = nullptr;
	Renderable(SDL_Renderer* renderer, std::string fileName, int x, int y, int w, int h)
	{
		location = new SDL_Rect();
		location->x = x;
		location->y = y;
		location->w = h;
		location->h = h;
	}
	void render(SDL_Surface* window, SDL_Renderer* renderer)
	{
		SDL_RenderCopy(renderer, getSprite(), NULL, location);
	}
	virtual SDL_Texture* getSprite() = 0;
	~Renderable()
	{
		delete location;
		location = nullptr;
	}
};