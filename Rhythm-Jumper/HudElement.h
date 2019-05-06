#pragma once
class HudElement
{
public:
	HudElement()
	{

	}
	virtual void render(SDL_Renderer* renderer) = 0;
	~HudElement()
	{

	}
};