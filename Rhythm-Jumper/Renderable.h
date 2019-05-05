#pragma once
#include "Rectangle.h"
class Renderable
{
protected:
	Rectangle* location = nullptr;
public:
	Renderable(SDL_Renderer* renderer, int x, int y, int w, int h)
	{
		location = new Rectangle(x, y, w, h);
	}
	void render(SDL_Surface* window, SDL_Renderer* renderer)
	{
		SDL_RenderCopy(renderer, getSprite(), NULL, location->getSDL_Rect());
	}
	virtual SDL_Texture* getSprite() = 0;
	~Renderable()
	{
		delete location;
		location = nullptr;
	}
};