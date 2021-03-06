#pragma once
#include "State.h"
#include "Player.h"
#include "Ball.h"
#include "XML_Level.h"
#include "BrickMap.h"
#include "PauseMenu.h"
#include "ScoreSystem.h"
#include "CollisionSystem.h"
#include "WinLoseMenu.h"


class GameState : public State
{
private:
	int currentLife;
	int level;

	sf::Texture backgroundTexture;
	sf::SoundBuffer buffer;
	
	
	sf::RectangleShape background;
	sf::Font font;

	ScoreSystem* scoreSystem;
	CollisionSystem* collisionSystem;
	Player* player;
	Ball* ball;

	PauseMenu* pmenu;
	WinLoseMenu* wmenu;
	bool restartStateVar;

	XML_Level* levelData;
	BrickMap* brickMap;
	//Functions

	void initKeybinds();
	void initFonts();
	void initTextures();
	void initBackground();
	void initPlayers();
	void initMenus();
	void initXMLLevel();
	void initBrickMap();
	void initScoreSystem();
	void initCollisionSystem();
	void loadSound();
public:
	GameState(StateData* stateData,int level,int currentLife);
	virtual ~GameState();


	//Functions
	void updateCollisions(const float& dt);
	void updatePauseMenuButtons();
	void updateWinLoseMenuButtons();
	void updateInput(const float& dt);
	void updateGameState();
	void updatePlayerInput(const float& dt);
	void updateBallPosition(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
	State* getRestart() const;
};
