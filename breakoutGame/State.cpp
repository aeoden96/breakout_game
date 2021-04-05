#include "State.h"

State::State(StateData* stateData)
{

	this->stateData = stateData;
	this->window = stateData->window;
	this->states = stateData->states;
	this->supportedKeys = stateData->supportedKeys;
	this->quit = false;
	this->paused = false;
	this->currentState = gameState::PLAYING;
	this->keytime = 0.f;
	this->keytimeMax = 10.f;
	this->gridSize = stateData->gridSize;
}


State::~State()
{

}

gameState State::getQuit() const
{
	return this->currentState;
	//return this->quit;
}

State* State::getRestart() const
{
	return nullptr;
}

const bool State::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	return false;
}


//Functions
void State::endState(gameState state)
{
	//this->quit = true;
	this->currentState = state;
}


void State::pauseState()
{
	this->currentState = gameState::PAUSED;
	this->paused = true;
}

void State::unpauseState()
{
	this->currentState = gameState::PLAYING;
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