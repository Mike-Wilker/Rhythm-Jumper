#pragma once
#include "Barrier.h"
class Fence : public Barrier
{
private:
	const char spriteFileName[27] = "resources//placeholder.bmp";
	static SDL_Texture* sprite;
	const double movementSpeed = -1.0;
public:
	Fence(SDL_Renderer* renderer, int x, int y, int w, int h) : Barrier(renderer, x, y, w, h)
	{
		if (sprite == nullptr)
		{
			SDL_Surface* image = SDL_LoadBMP(spriteFileName);
			sprite = SDL_CreateTextureFromSurface(renderer, image);
			SDL_FreeSurface(image);
		}
	}
	void update(int ticks) override
	{
		//location->offsetX(movementSpeed * ticks / 1000.0);
	}
	SDL_Texture* getSprite() override
	{
		return sprite;
	}
	~Fence()
	{

	}
};
SDL_Texture* Fence::sprite;