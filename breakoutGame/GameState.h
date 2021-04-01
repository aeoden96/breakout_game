#pragma once
#include "State.h"
#include "Player.h"
#include "Ball.h"
#include "XML_Level.h"
#include "BrickMap.h"
#include "PauseMenu.h"
#include "ScoreSystem.h"
#include "CollisionSystem.h"

class GameState : public State
{
private:

	sf::Texture backgroundTexture;
	sf::SoundBuffer buffer;
	
	
	sf::RectangleShape background;
	sf::Font font;

	ScoreSystem* scoreSystem;
	CollisionSystem* collisionSystem;
	Player* player;
	Ball* ball;
	PauseMenu* pmenu;
	XML_Level* level;
	BrickMap* brickMap;
	//Functions

	void initKeybinds();
	void initFonts();
	void initTextures();
	void initBackground();
	void initPlayers();
	void initPauseMenu();
	void initXMLLevel();
	void initBrickMap();
	void initScoreSystem();
	void initCollisionSystem();
	void loadSound();
public:
	GameState(StateData* stateData);
	virtual ~GameState();


	//Functions
	void updateCollisions(const float& dt);
	void updatePauseMenuButtons();
	void updateInput(const float& dt);
	void updateGameState();
	void updatePlayerInput(const float& dt);
	void updateBallPosition(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};
