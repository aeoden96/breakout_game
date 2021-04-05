#include "ScoreSystem.h"
#include"libs.h"

void ScoreSystem::addPoints(char brickType)
{
	score += level->brickMap.at(brickType).breakScore;

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



ScoreSystem::ScoreSystem(XML_Level* level,sf::Font& font):
	level(level),font(font)
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
}
