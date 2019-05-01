#pragma once
#include <string>
#include "GameObject.h"
#include "Barrier.h"
#include "Keyhandler.h"
constexpr double BARRIER_DAMAGE = 10.0;
constexpr double HEALTH_REGEN = 50.0;
class Player : public GameObject
{
private:
	static SDL_Texture* sprite;
	float health;
public:
	Player(SDL_Renderer* renderer, std::string fileName, int x, int y, int w, int h) : GameObject(renderer, fileName, x, y, w, h)
	{
		health = 100.0;
		if (sprite == nullptr)
		{
			SDL_Surface* image = SDL_LoadBMP(fileName.c_str());
			sprite = SDL_CreateTextureFromSurface(renderer, image);
			SDL_FreeSurface(image);
		}
	}
	void update(int ticks) override
	{

	}
	void update(std::vector<Barrier*> barriers, int ticks)
	{
		health += HEALTH_REGEN * (ticks / 1000.0);
		for (Barrier* barrier : barriers)
		{
			if (checkCollision(barrier))
			{
				health -= BARRIER_DAMAGE;
				barrier->hit();
			}
		}
	}
	SDL_Texture* getSprite() override
	{
		return sprite;
	}
	void handleInput()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_SPACE)
				{
					std::cout << "yes";
				}
				break;
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_SPACE)
				{

				}
				break;
			default:
				break;
			}
		}
	}
	~Player()
	{

	}
};
SDL_Texture* Player::sprite;