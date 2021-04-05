#include "libs.h"
#include "GameState.h"



//Initializer functions
void GameState::initKeybinds()
{

	std::ifstream ifs("Config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{

		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = supportedKeys->at(key2);

		}
	}
	ifs.close();

	/*std::cout << "\nGameState:Keybinds map: \n";
	for (auto i : this->keybinds)
	{
		std::cout << "   > " << i.first << " " << i.second << "\n";
	}*/
}

void GameState::initFonts()
{

	//std::cout << "\n" << "---MainMenuState initFonts  ";
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::GameState::COULD_NOT_LOAD_FONT");
	}
}

void GameState::initTextures()
{

	/*if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/player_sheet.png"))
	{
		throw "ERROR:GAME_STATE:COULD_NOT_LOAD_PLAYER_TEXTURE";
	}*/
	if (!this->textures["PLAYER_TEXTURE"].loadFromFile("Resources/Images/player.png"))
	{
		throw "ERROR:GAME_STATE:COULD_NOT_LOAD_PLAYER_TEXTURE";
	}

	if (!this->textures["BALL_TEXTURE"].loadFromFile("Resources/Images/ball.png"))
	{
		throw "ERROR:GAME_STATE:COULD_NOT_LOAD_PLAYER_TEXTURE";
	}

	//std::cout << "\n\nGamestate::initTextures player tex\n";


}

void GameState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);
	if (!this->backgroundTexture.loadFromFile(this->level->backgroundTexture))
		throw "ERROR:MAINMENUSTATE:FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	this->background.setTexture(&this->backgroundTexture);

}

void GameState::initPlayers()
{
	this->player = new Player(
		this->stateData->gfxSettings->resolution.width  * 0.5f, 
		this->stateData->gfxSettings->resolution.height * 0.8f, 
		this->textures["PLAYER_TEXTURE"]);

	this->player->setTexture(textures["PLAYER_TEXTURE"]);

	this->ball = new Ball(
		this->stateData->gfxSettings->resolution.width * 0.5f,
		this->stateData->gfxSettings->resolution.height * 0.5f
		, this->textures["BALL_TEXTURE"]);

	this->ball->setTexture(textures["BALL_TEXTURE"]);



}

void GameState::initMenus()
{
	this->pmenu = new PauseMenu(*this->window, this->font);
	this->pmenu->addButton("QUIT", 930.f, "Quit");

	this->wmenu = new WinLoseMenu(*this->window, this->font);
	this->wmenu->addButton("NEXT", 830.f, "Try next level");
	this->wmenu->addButton("QUIT", 930.f, "Quit");
}

void GameState::initXMLLevel(int level)
{
	this->level = new XML_Level();
	this->level->importDataForLevel(level);
}

void GameState::initBrickMap()
{//why gamestate has tilemap?

	this->brickMap = new BrickMap(
		/*this->stateData->gridSize*/ 100, 10, 10,
		"Resources/Images/box_textures.png",
		this->level,
		this->scoreSystem,
		&buffer);
}

void GameState::initScoreSystem() {
	this->scoreSystem = new ScoreSystem(level,font);
	
}
void GameState::initCollisionSystem() {
	this->collisionSystem =
		new CollisionSystem(ball, player, brickMap,scoreSystem);

}
void GameState::loadSound() {
	if (!buffer.loadFromFile("Resources/Sounds/break_sound1.wav"))
		return;
}
//Const/destr
GameState::GameState(StateData* stateData, int level)
	:State(stateData)
{

	this->restartStateVar = false;

	this->initXMLLevel(level);
	this->loadSound();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initBackground();
	this->initMenus();
	this->initPlayers();
	this->initScoreSystem();
	this->initBrickMap();
	this->initCollisionSystem();

}


GameState::~GameState()
{


	delete this->level;
	delete this->player;
	delete this->ball;
	delete this->pmenu;
	delete this->brickMap;
	delete this->scoreSystem;
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
	{
		this->endState(gameState::QUIT);
	}
}

void GameState::updateWinLoseMenuButtons()
{
	if (this->wmenu->isButtonPressed("QUIT"))
	{
		this->endState(gameState::QUIT);
	}

	if (this->wmenu->isButtonPressed("NEXT"))
	{
		this->endState(gameState::RESTART);
	}
}

void GameState::updateCollisions(const float& dt) {
	this->collisionSystem->update(dt);	
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Close"))) && this->getKeytime())
	{
		//this->endState();


		if (this->currentState == gameState::PLAYING)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updateGameState() {
	if (this->scoreSystem->gameState() == gameState::LOST)
	{
		this->currentState = gameState::LOST;
		this->wmenu->setFinishScreen(gameState::LOST);
		//this->endState();

		
	}
		
}	

void GameState::updatePlayerInput(const float& dt)
{
	

	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(1.f, 0.f, dt);
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("ACTION"))))
		this->player->action(dt);*/


	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player->move(0.f, 1.f, dt);*/




}
void GameState::updateBallPosition(const float& dt) {
	this->ball->move(dt);
}


void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeytime(dt);
	this->updateInput(dt);
	if(this->currentState == gameState::PLAYING)
	//if (!this->paused) //unpaused update
	{
		this->updatePlayerInput(dt); //update keyboard player movement
		this->updateCollisions(dt);
		this->updateBallPosition(dt);

		this->player->update(dt); 
		this->ball->update(dt);
		this->scoreSystem->update();

		this->updateGameState();

	}
	//else if (this->paused) //Paused update
	else if(this->currentState == gameState::PAUSED)
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
	else if (this->currentState == gameState::WON || this->currentState == gameState::LOST) {
		this->wmenu->update(this->mousePosWindow);
		this->updateWinLoseMenuButtons();

	}

}

void GameState::render(sf::RenderTarget* target)
{
	//if target window not given,will render to default window
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->player->render(*target);

	this->ball->render(*target);

	this->brickMap->render(*target);

	this->scoreSystem->render(*target);

	//if (this->paused)//Pause menu render
	if(this->currentState == gameState::PAUSED)
	{
		this->pmenu->render(*target);
	}
	if (this->currentState == gameState::WON || this->currentState == gameState::LOST)
	{
		this->wmenu->render(*target);
	}


}

State* GameState::getRestart() const
{
	return new GameState(this->stateData, 2);
}
