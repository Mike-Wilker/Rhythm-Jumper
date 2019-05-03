#pragma once
#include "SDL_rect.h"
class Rectangle : protected SDL_Rect
{
public:
	double xOffset;
	double yOffset;
	Rectangle()
	{
		this->xOffset = 0.0;
		this->yOffset = 0.0;
	}
	Rectangle(int x, int y, int w, int h)
	{
		this->xOffset = 0.0;
		this->yOffset = 0.0;
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
	void offsetX(int offset)
	{
		xOffset += offset;
	}
	void offsetY(int offset)
	{
		yOffset += offset;
	}
	const SDL_Rect* getSDL_Rect()
	{
		this->x += round(xOffset);
		xOffset -= round(xOffset);
		this->y += round(yOffset);
		yOffset -= round(yOffset);
		return (SDL_Rect*)this;
	}
	bool checkCollision(Rectangle* other)
	{
		return SDL_HasIntersection(this->getSDL_Rect(), other->getSDL_Rect());
	}
	~Rectangle()
	{

	}
};