#pragma once
#include"libs.h"
#include"Brick.h"
#include "XML_Level.h"
#include"Entity.h"
#include "Ball.h"
#include "Player.h"
#include "ScoreSystem.h"

class BrickMap
{
private:
	float gridSizeF;
	unsigned gridSizeU;
	unsigned layers;

	ScoreSystem* scoreSystem;
	XML_Level* levelInfo;
	//sf::Sound sound;
	
	std::vector< std::vector< std::vector<Brick* > > > map; //XYZ coord 
	std::string textureFile;
	sf::Texture tileTextureSheet;
	//std::map<BrickT,sf::IntRect> crackMap;
	//now we can have null pointers in entire map
	std::map<char, sf::Music> breakSounds;
	std::map<char, sf::Music> hitSounds;


	void clear();

public:
	sf::Vector2u maxSize;
	
	Brick* returnBrick(int i, int j);
	void crackIt(int i, int j);

	BrickMap(float gridSize,
		unsigned width, 
		unsigned hight, 
		std::string textureFile,
		XML_Level* levelInfo,
		ScoreSystem* scoreSystem);
	virtual ~BrickMap();

	//Accessors 
	const sf::Texture* getTileSheet() const;

	//Functions 
	void saveToFile(const std::string fileName);
	void loadFromFile(const std::string fileName);

	void playSound(bool brickBroken, char brickType);

	//void updateBrickCollision(Entity* entity, const float& dt);
	
	//void updateBricks(Entity* entity, const float& dt);

	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& tex_rect, const bool& collision, const bool& type);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	void update();
	void render(sf::RenderTarget& target);


};