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

	std::cout << "\nGameState:Keybinds map: \n";
	for (auto i : this->keybinds)
	{
		std::cout << "   > " << i.first << " " << i.second << "\n";
	}
}

void GameState::initFonts()
{

	std::cout << "\n" << "---MainMenuState initFonts  ";
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

	std::cout << "\n\nGamestate::initTextures player tex\n";


}

void GameState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);
	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/background2.jpg"))
		throw "ERROR:MAINMENUSTATE:FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	this->background.setTexture(&this->backgroundTexture);

}

void GameState::initPlayers()
{
	this->player = new Player(800, 800, this->textures["PLAYER_TEXTURE"]);

	this->player->setTexture(textures["PLAYER_TEXTURE"]);

	this->ball = new Ball(500, 500, this->textures["BALL_TEXTURE"]);

	this->ball->setTexture(textures["BALL_TEXTURE"]);



}

void GameState::initPauseMenu()
{
	//this->pmenu = new PauseMenu(*this->window, this->font);
	//this->pmenu->addButton("QUIT", 930.f, "Quit");
}

void GameState::initTileMap()
{//why gamestate has tilemap?
	//this->tileMap = new TileMap(this->stateData->gridSize, 10, 10, "Resources/Images/Tiles/tilesheet1.png");
}

//Const/destr
GameState::GameState(StateData* stateData)
	:State(stateData)
{
	std::cout << "GameState constructor \n";

	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initBackground();
	this->initPauseMenu();
	this->initPlayers();
	this->initTileMap();

	this->level.importDataForLevel(0);

}

GameState::~GameState()
{
	std::cout << "\n" << "GameState destr";
	//delete this->player;
	//delete this->pmenu;
	//delete this->tileMap;
}

void GameState::updatePauseMenuButtons()
{
	/*if (this->pmenu->isButtonPressed("QUIT"))
	{
		this->endState();
	}*/
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Close"))) && this->getKeytime())
	{
		this->endState();


		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
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

	if (!this->paused) //unpaused update
	{
		this->updatePlayerInput(dt); //update keyboard player movement

		this->updateBallPosition(dt);

		this->player->update(dt); 

		this->ball->update(dt);
	}
	else if (this->paused) //Paused update
	{

		//this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();

	}

}

void GameState::render(sf::RenderTarget* target)
{
	//if target window not given,will render to default window
	if (!target)
		target = this->window;

	target->draw(this->background);

	//this->map.render(*target);

	this->player->render(*target);

	this->ball->render(*target);

	if (this->paused)//Pause menu render
	{
		///this->pmenu->render(*target);
	}


}