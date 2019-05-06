#pragma once
class Bar : public HudElement
{
protected:
	Rectangle* location;
	double max;
	double value;
	const double BORDER_THICKNESS = 5;
	SDL_Color barColor;
	SDL_Color baseColor = { 0xFF, 0x00, 0x00, 0xFF };
public:
	Bar(int x, int y, int w, int h, SDL_Color barColor) : HudElement()
	{
		location = new Rectangle(x, y, w, h);
		this->barColor = barColor;
	}
	void render(SDL_Renderer* renderer) override
	{
		SDL_SetRenderDrawColor(renderer, baseColor.r, baseColor.g, baseColor.b, baseColor.a);
		SDL_RenderFillRect(renderer, location->getSDL_Rect());
		SDL_SetRenderDrawColor(renderer, barColor.r, barColor.g, barColor.b, barColor.a);
		SDL_Rect bar;
		bar.x = location->getX() + BORDER_THICKNESS;
		bar.y = location->getY() + BORDER_THICKNESS;
		bar.w = (int) (getFill() * location->getW()) - (2*BORDER_THICKNESS);
		bar.h = location->getH() - (2*BORDER_THICKNESS);
		SDL_RenderFillRect(renderer, &bar);
	}
	virtual double getFill() = 0;
	~Bar()
	{

	}
};
