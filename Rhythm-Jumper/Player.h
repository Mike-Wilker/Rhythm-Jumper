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
	const char spriteFileName[27] = "resources//placeholder.bmp";
	static SDL_Texture* sprite;
	double health;
	KeyHandler* keyHandler;
public:
	Player(SDL_Renderer* renderer, int x, int y, int w, int h) : GameObject(renderer, x, y, w, h)
	{
		health = 100.0;
		if (sprite == nullptr)
		{
			SDL_Surface* image = SDL_LoadBMP(spriteFileName);
			sprite = SDL_CreateTextureFromSurface(renderer, image);
			SDL_FreeSurface(image);
		}
		keyHandler = new KeyHandler();
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
				barrier->hit();
				health -= BARRIER_DAMAGE;
			}
		}
	}
	SDL_Texture* getSprite() override
	{
		return sprite;
	}
	void handleInput()
	{
		for (char key : keyHandler->getPressedKeys())
		{
			switch (key)
			{
			case ' ':

				break;
			case 'w':
				break;
			case 's':
				break;
			case 'a':
				break;
			case 'd':
				break;
			}
		}
	}
	~Player()
	{
		SDL_DestroyTexture(sprite);
	}
};
SDL_Texture* Player::sprite;