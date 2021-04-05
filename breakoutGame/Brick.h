#pragma once
#include"libs.h"
#include "XML_Level.h"


enum TileTypes { DEFAULT = 0, DAMAGING };


class Brick
{
private:

protected:
	//sf::Sprite shape;
	sf::RectangleShape shape;
	short type;
	bool collision;
	bool isHit;
	std::string id;
	char brickType;
	int hitsToCrack;

public:
	Brick(
		unsigned grid_x,
		unsigned grid_y,
		float gridSizeF_x,
		float gridSizeF_y,
		const sf::Texture& texture,
		const sf::IntRect& tex_rect,
		bool collision = false,
		short type = TileTypes::DEFAULT,
		char id= brickTypeClass::UNDEF,
		int hitsToCrack=1);
	void crackIt(int posX, int posY, int sizeX, int sizeY);
	Brick();
	virtual ~Brick();
	//Functions
	sf::FloatRect returnPosition();
	void hit();
	const std::string getAsString() const;
	char getBrickType();
	int getCrackNum();
	void update();
	void render(sf::RenderTarget& target);
};
