#pragma once
#include "XML_Level.h"


class ScoreSystem
{
private:
	XML_Level* levelData;
	int level;
	int currentLife;

	sf::Font font;
	sf::Text scoreText;
	sf::Text levelText;
	sf::Text lifeText;

	gameState currentState;

	unsigned int score = 0;
public:
	void addPoints(char brickType);
	gameState gameState();
	int getScore();
	void ballLost();

	ScoreSystem(XML_Level* levelData,sf::Font& font,int level,int currentLife);
	~ScoreSystem();

	void update();
	void render(sf::RenderTarget& target);


};

