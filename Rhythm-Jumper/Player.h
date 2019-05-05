#pragma once
#include <string>
#include <list>
#include "GameObject.h"
#include "Barrier.h"
#include "KeyHandler.h"
constexpr double BARRIER_DAMAGE = 10.0;
constexpr double MAX_HEALTH = 100.0;
constexpr double HEALTH_REGEN = 50.0;
constexpr double JUMP_SPEED = 1000.0;
constexpr double GRAVITY = 4000.0;
class Player : public GameObject
{
private:
	const static int GROUND_DEPTH = 700;
	const static int startX = 200;
	const static int width = 100;
	const static int height = 100;
	const char SPRITE_FILE_NAME[27] = "resources//placeholder.bmp";
	static SDL_Texture* sprite;
	double health;
	double ySpeed;
public:
	Player(SDL_Renderer* renderer) : GameObject(renderer, startX, GROUND_DEPTH, width, height)
	{
		ySpeed = 0;
		health = MAX_HEALTH;
		if (sprite == nullptr)
		{
			SDL_Surface* image = SDL_LoadBMP(SPRITE_FILE_NAME);
			sprite = SDL_CreateTextureFromSurface(renderer, image);
			SDL_FreeSurface(image);
		}
	}
	void update(int ticks) override
	{

	}
	void update(std::list<Barrier*> barriers, KeyHandler* keyHandler, int ticks)
	{
		health += HEALTH_REGEN * (ticks / 1000.0);
		if (onGround())
		{
			ySpeed = 0;
		}
		else
		{
			ySpeed -= (GRAVITY * ticks / 1000.0);
		}
		for (Barrier* barrier : barriers)
		{
			if (checkCollision(barrier))
			{
				barriers.remove(barrier);
				health -= BARRIER_DAMAGE;
			}
		}
		handleInput(keyHandler, ticks);
		location->offsetY(-ySpeed * ticks / 1000.0);
	}
	SDL_Texture* getSprite() override
	{
		return sprite;
	}
	void handleInput(KeyHandler* keyHandler, int ticks)
	{
		std::list<SDL_Keycode> keys = keyHandler->getHeldKeys();
		for (SDL_Keycode key : keys)
		{
			switch (key)
			{
			case SDLK_w:
				jumpCommand(ticks);
				break;
			}
		}
	}
	void jumpCommand(int ticks)
	{
		if (onGround())
		{
			ySpeed = JUMP_SPEED;
		}
	}
	bool onGround()
	{
		return location->getY() >= GROUND_DEPTH;
	}
	~Player()
	{
		SDL_DestroyTexture(sprite);
	}
};
SDL_Texture* Player::sprite = nullptr;
