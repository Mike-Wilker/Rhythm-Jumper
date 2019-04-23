#pragma once
#include <string>
#include "GameObject.h"
class Player : public GameObject
{
public:
	Player(std::string fileName, int x, int y, int w, int h) : GameObject(fileName, x, y, w, h)
	{

	}
	void update() override
	{

	}
	~Player()
	{

	}
};