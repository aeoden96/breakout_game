#pragma once
#include "State.h"
#include "Player.h"
#include "Ball.h"
#include "XML_Level.h"
#include "BrickMap.h"
//#include "PauseMenu.h"
//#include "TileMap.h"
class GameState : public State
{
private:
	Player* player;
	Ball* ball;
	//PauseMenu* pmenu;
	XML_Level* level;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

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
public:
	GameState(StateData* stateData);
	virtual ~GameState();


	//Functions
	void updatePauseMenuButtons();
	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updateBallPosition(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};
