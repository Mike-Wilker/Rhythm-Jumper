#pragma once
#include <SDL.h>
class Rectangle : private SDL_Rect
{
private:
	double xOffset;
	double yOffset;
public:
	Rectangle() : SDL_Rect()
	{
		this->xOffset = 0.0;
		this->yOffset = 0.0;
	}
	Rectangle(int x, int y, int w, int h) : Rectangle()
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
	void offsetX(double offset)
	{
		this->xOffset += offset;
		this->x += (int) round(xOffset);
		this->xOffset -= round(xOffset);
	}
	void offsetY(double offset)
	{
		this->yOffset += offset;
		this->y += (int) round(yOffset);
		this->yOffset -= round(yOffset);
	}
	int getX()
	{
		return this->x;
	}
	int getY()
	{
		return this->y;
	}
	const SDL_Rect* getSDL_Rect()
	{
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