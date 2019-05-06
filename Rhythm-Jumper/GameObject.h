#pragma once
class GameObject : public Renderable
{
protected:
	bool deletable;
public:
	GameObject(SDL_Renderer* renderer, int x, int y, int w, int h) : Renderable(renderer, x, y, w, h)
	{
		deletable = false;
	}
	virtual void update(int ticks) = 0;
	const bool checkCollision(GameObject* other)
	{
		return (!other->isDeletable() && this->location->checkCollision(other->location));
	}
	const bool isDeletable()
	{
		return deletable;
	}
	~GameObject()
	{

	}
};