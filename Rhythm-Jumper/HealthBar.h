#pragma once
class HealthBar : public Bar
{
	const static int X = 20;
	const static int Y = 20;
	const static int W = 500;
	const static int H = 50;
	const static SDL_Color barColor;
	Player* player;
public:
	HealthBar(Player* player) : Bar(X, Y, W, H, barColor)
	{
		this->player = player;
	}
	double getFill() override
	{
		return (player->getHealth() / MAX_HEALTH);
	}
	~HealthBar()
	{

	}
};
const SDL_Color HealthBar::barColor = { 0x00, 0xFF, 0x00, 0xFF };