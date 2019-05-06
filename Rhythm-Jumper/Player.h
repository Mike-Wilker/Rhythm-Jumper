#pragma once
constexpr double BARRIER_DAMAGE = 50.0;
constexpr double MAX_HEALTH = 100.0;
constexpr double HEALTH_REGEN = 10.0;
constexpr double JUMP_SPEED = 1000.0;
constexpr double GRAVITY = 4000.0;
class Player : public GameObject
{
private:
	const static int GROUND_DEPTH = 700;
	const static int START_X = 200;
	const static int WIDTH = 100;
	const static int HEIGHT = 100;
	const static int SCORE_GAIN = 10;
	const char SPRITE_FILE_NAME[27] = "resources//placeholder.bmp";
	static SDL_Texture* sprite;
	double health;
	double score;
	double ySpeed;
public:
	Player(SDL_Renderer* renderer) : GameObject(renderer, START_X, GROUND_DEPTH, WIDTH, HEIGHT)
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
		health = health + (HEALTH_REGEN * ticks / 1000.0) < MAX_HEALTH ? health + (HEALTH_REGEN * ticks / 1000.0) : MAX_HEALTH;
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
				barrier->hit();
				health -= BARRIER_DAMAGE;
			}
			else
			{
				tryScore(barrier);
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
	void tryScore(Barrier* barrier)
	{
		if (barrier->getLocation()->getX() < getLocation()->getX())
		{
			if (barrier->tryScore())
			{
				score += SCORE_GAIN;
			}
		}
	}
	const bool onGround()
	{
		return location->getY() >= GROUND_DEPTH;
	}
	const double getHealth()
	{
		return health;
	}
	~Player()
	{
		SDL_DestroyTexture(sprite);
	}
};
SDL_Texture* Player::sprite = nullptr;
