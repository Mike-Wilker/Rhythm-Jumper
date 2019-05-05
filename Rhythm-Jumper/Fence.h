#pragma once
#include "Barrier.h"
class Fence : public Barrier
{
private:
	const char SPRITE_FILE_NAME[27] = "resources//placeholder.bmp";
	static SDL_Texture* sprite;
	const double MOVEMENT_SPEED = 1000.0;
	const static int WIDTH = 100;
	const static int HEIGHT = 50;
	const static int GROUND_DEPTH = 700;
public:
	Fence(SDL_Renderer* renderer, int x) : Barrier(renderer, x, GROUND_DEPTH + HEIGHT, WIDTH, HEIGHT)
	{
		if (sprite == nullptr)
		{
			SDL_Surface* image = SDL_LoadBMP(SPRITE_FILE_NAME);
			sprite = SDL_CreateTextureFromSurface(renderer, image);
			SDL_FreeSurface(image);
		}
	}
	void update(int ticks) override
	{
		location->offsetX(-MOVEMENT_SPEED * (ticks / 1000.0));
		if (location->getX() < 0)
		{
			deletable = true;
		}
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