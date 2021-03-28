#pragma once
#include"libs.h"

enum TileTypes { DEFAULT = 0, DAMAGING };

class Brick
{
private:

protected:
	sf::RectangleShape shape;
	short type;
	bool collision;

public:
	Brick(unsigned grid_x, unsigned grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& tex_rect, bool collision = false, short type = TileTypes::DEFAULT);
	Brick();
	virtual ~Brick();
	//Functions
	const std::string getAsString() const;
	void update();
	void render(sf::RenderTarget& target);
};
