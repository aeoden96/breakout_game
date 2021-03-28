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

	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/player_sheet.png"))
	{
		throw "ERROR:GAME_STATE:COULD_NOT_LOAD_PLAYER_TEXTURE";
	}


}

void GameState::initPlayers()
{
	//this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);

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
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initPlayers();
	this->initTileMap();

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
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updatePlayerInput(const float& dt)
{

	////Update player input
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
	//	this->player->move(-1.f, 0.f, dt);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
	//	this->player->move(1.f, 0.f, dt);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
	//	this->player->move(0.f, -1.f, dt);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
	//	this->player->move(0.f, 1.f, dt);


}

void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused) //unpaused update
	{
		this->updatePlayerInput(dt); //update keyboard player movement

		//this->player->update(dt); //update other
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

	//this->map.render(*target);

	///this->player->render(*target);

	if (this->paused)//Pause menu render
	{
		///this->pmenu->render(*target);
	}


}