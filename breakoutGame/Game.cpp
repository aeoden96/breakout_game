#include "libs.h"
#include "Game.h"
#include "State.h"
#include "MainMenuState.h"

//Static functions


void Game::initVariables()
{
	this->window = NULL;
	this->dt = 0.f;

	this->gridSize = 100.f;

}

void Game::initGraphicsSettings()
{
	this->gfxSettings.loadFromFile("Config/graphics.ini");
}

void Game::initWindow()
{
	/*Creates SFML window*/

	this->window = new sf::RenderWindow(
		this->gfxSettings.resolution,
		this->gfxSettings.title,
		(this->gfxSettings.fullscreen) ? sf::Style::Fullscreen :(sf::Style::Titlebar | sf::Style::Close),
		this->gfxSettings.contextSettings
	);

	this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
	this->window->setVerticalSyncEnabled(this->gfxSettings.vsync);
}

void Game::initKeys()
{
	std::ifstream ifs("Config/supportedKeys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;
		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;
		}
	}
	ifs.close();

	std::cout << "SupportedKeys map: \n";
	for (auto i : this->supportedKeys)
	{
		std::cout << "   > " << i.first << " " << i.second << "\n";
	}




}

void Game::initStateData()
{
	//copying pointer values to stateData object.
	this->stateData.window = this->window;
	this->stateData.gfxSettings = &this->gfxSettings;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
	this->stateData.gridSize = this->gridSize;

}



void Game::initStates()
{
	this->states.push(new MainMenuState(&this->stateData));
	//this->states.push(new GameState(this->window,&this->supportedKeys));
}



//Constructors
Game::Game()
{
	this->initVariables();
	this->initGraphicsSettings();
	this->initWindow();
	this->initKeys();
	this->initStateData();
	this->initStates();

}

//Destructors
Game::~Game()
{
	delete this->window;
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}


}

//Functions

void Game::endApplication()
{
	std::cout << "\nEnding app...\n\n";
}

void Game::updateDt()
{
	/*Updates dt variable with time it takes to update and render one frame*/
	this->dt = this->dtClock.restart().asSeconds();

}

void Game::update()
{
	this->updateSFMLEvents();

	//if there is AT LEAST ONE state on stack
	if (!this->states.empty())
	{
		//update the top state
		this->states.top()->update(this->dt);


		if (this->states.top()->getQuit() == gameState::QUIT || this->states.top()->getQuit() == gameState::RESTART)
		{
			if (this->states.top()->getQuit() == gameState::RESTART) {
				State* requestedRestartedState = this->states.top()->getRestart();
				this->states.top()->endState(gameState::RESTART);
				delete this->states.top();
				this->states.pop();

				this->states.push(requestedRestartedState);
				return;

			}
			this->states.top()->endState(gameState::QUIT);
			//delete state the top pointer points to
			delete this->states.top();

			this->states.pop();
		}

	}


	//Application end
	else
	{
		//insted of destructor 
		this->endApplication();
		this->window->close();

	}



}

void Game::render()
{
	this->window->clear();

	//Render items

	if (!this->states.empty())
		this->states.top()->render(this->window);



	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
}