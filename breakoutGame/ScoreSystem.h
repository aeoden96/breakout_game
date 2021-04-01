#pragma once
#include "XML_Level.h"

enum gameState {PLAYING , LOST ,WON};
class ScoreSystem
{
private:
	XML_Level* level;

	sf::Font font;
	sf::Text scoreText;

	gameState currentState;

	unsigned int score = 0;
public:
	void addPoints(BrickT brickType);
	gameState gameState();
	int getScore();
	void ballLost();

	ScoreSystem(XML_Level* level,sf::Font& font);
	~ScoreSystem();

	void update();
	void render(sf::RenderTarget& target);


};

