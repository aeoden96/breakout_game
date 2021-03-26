#include "State.h"

State::State(StateData* stateData)
{

	std::cout << "\n" << "State constr";
	this->stateData = stateData;
	this->window = stateData->window;
	this->states = stateData->states;
	this->supportedKeys = stateData->supportedKeys;
	this->quit = false;
	this->paused = false;
	this->keytime = 0.f;
	this->keytimeMax = 10.f;
	this->gridSize = stateData->gridSize;
}


State::~State()
{
	std::cout << "\n" << "State destr \n \n";

}
//Accessors
const bool& State::getQuit() const
{
	return this->quit;
}

const bool& State::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	return false;
}


//Functions
void State::endState()
{
	this->quit = true;
}

void State::pauseState()
{
	this->paused = true;
}

void State::unpauseState()
{
	this->paused = false;
}



void State::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
	{

		this->keytime += 100.f * dt;
	}
}

void State::updateMousePositions(sf::View* view)
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);

	if (view)
		this->window->setView(*view);

	this->mousePosView = this->stateData->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePosGrid =
		sf::Vector2u(
			static_cast<unsigned>(this->mousePosView.x) / static_cast<unsigned>(this->gridSize),
			static_cast<unsigned>(this->mousePosView.y) / static_cast<unsigned>(this->gridSize)
		);

	this->window->setView(this->window->getDefaultView());
}