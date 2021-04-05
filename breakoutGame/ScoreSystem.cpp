#include "ScoreSystem.h"
#include"libs.h"

void ScoreSystem::addPoints(char brickType)
{
	score += levelData->brickMap.at(brickType).breakScore;

}

gameState ScoreSystem::gameState()
{
	return currentState;
}

int ScoreSystem::getScore()
{
	return score;
}

void ScoreSystem::ballLost()
{
	currentState = gameState::LOST;
}



ScoreSystem::ScoreSystem(XML_Level* levelData,sf::Font& font,int level, int currentLife):
	levelData(levelData),font(font),level(level),currentLife(currentLife)
{
	if (!font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::GameState::COULD_NOT_LOAD_FONT");
	}

	//init text
	this->scoreText.setFont(font);
	this->scoreText.setFillColor(sf::Color(255, 255, 255, 200));
	this->scoreText.setCharacterSize(60);
	this->scoreText.setString("SCORE");
	this->scoreText.setPosition(20, 0);

	this->levelText.setFont(font);
	this->levelText.setFillColor(sf::Color(255, 255, 255, 200));
	this->levelText.setCharacterSize(60);
	this->levelText.setString("Level: " + std::to_string(level));
	this->levelText.setPosition(400, 0);

	this->lifeText.setFont(font);
	this->lifeText.setFillColor(sf::Color(255, 255, 255, 200));
	this->lifeText.setCharacterSize(60);
	this->lifeText.setString("LIFE: " + std::to_string(currentLife));
	this->lifeText.setPosition(700, 0);





	score = 0;
	//std::cout << "\n" << "score " + std::to_string(score);

	currentState = gameState::PLAYING;
}



ScoreSystem::~ScoreSystem()
{
}

void ScoreSystem::update()
{
	this->scoreText.setString("SCORE " + std::to_string(score));
}

void ScoreSystem::render(sf::RenderTarget& target)
{
	target.draw(this->scoreText);
	target.draw(this->lifeText);
	target.draw(this->levelText);
}
