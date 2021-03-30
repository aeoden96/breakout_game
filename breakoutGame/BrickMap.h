#pragma once
#include"libs.h"
#include"Brick.h"
#include "XML_Level.h"
#include"Entity.h"

class BrickMap
{
private:
	float gridSizeF;
	unsigned gridSizeU;
	unsigned layers;

	XML_Level* levelInfo;
	sf::Vector2u maxSize;
	std::vector< std::vector< std::vector<Brick* > > > map; //XYZ coord 
	std::string textureFile;
	sf::Texture tileTextureSheet;
	//now we can have null pointers in entire map

	void clear();

public:

	int checkCollision(Entity* e);

	BrickMap(float gridSize, unsigned width, unsigned hight, std::string textureFile);
	BrickMap(float gridSize, unsigned width, unsigned hight, std::string textureFile,XML_Level* levelInfo);
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