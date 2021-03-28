#pragma once
#include"libs.h"
#include"Brick.h"

class BrickMap
{
private:
	float gridSizeF;
	unsigned gridSizeU;
	unsigned layers;

	sf::Vector2u maxSize;
	std::vector< std::vector< std::vector<Brick* > > > map; //XYZ coord 
	std::string textureFile;
	sf::Texture tileTextureSheet;
	//now we can have null pointers in entire map

	void clear();

public:
	BrickMap(float gridSize, unsigned width, unsigned hight, std::string textureFile);
	virtual ~BrickMap();

	//Accessors 
	const sf::Texture* getTileSheet() const;

	//Functions 
	void saveToFile(const std::string fileName);
	void loadFromFile(const std::string fileName);

	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& tex_rect, const bool& collision, const bool& type);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	void update();
	void render(sf::RenderTarget& target);


};