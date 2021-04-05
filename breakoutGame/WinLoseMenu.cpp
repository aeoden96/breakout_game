#include "WinLoseMenu.h"



WinLoseMenu::WinLoseMenu(sf::RenderWindow& window, sf::Font& font)
	:font(font)
{
	//Init background
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x),
			static_cast<float>(window.getSize().y)
		)
	);
	this->background.setFillColor(sf::Color(20, 20, 20, 100));


	//Init container
	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x) / 4.f,
			static_cast<float>(window.getSize().y) / 2.f
		)
	);
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(
		static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f,
		30.f
	);
	//init text
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(60);
	this->menuText.setString("WIN/LOSE???");
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 40.f
	);
}

WinLoseMenu::~WinLoseMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void WinLoseMenu::setFinishScreen(gameState won_or_lost) {
	std::string finText = won_or_lost == gameState::WON ? "YOU WON" : "YOU LOST";
	this->menuText.setString(finText);

	std::string finButtonText = won_or_lost == gameState::WON ? "Next level" : "Still try next level";
	this->buttons["NEXT"]->setText(finButtonText);

		
}


//Accessor
std::map<std::string, gui::Button*>& WinLoseMenu::getButtons()
{
	return this->buttons;
}

//Functions
const bool WinLoseMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}


void WinLoseMenu::pauseGraphics()
{

}


/*Adds a button to the PAUSE-MENU
*/
void WinLoseMenu::addButton(const std::string key, float y, const std::string text)
{
	float width = 400.f;
	float height = 50.f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	this->buttons[key] = new gui::Button(x, y, width, height,
		&this->font, text, 50,
		sf::Color(150, 150, 150, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

void WinLoseMenu::update(const sf::Vector2i& mousePosWindow)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePosWindow);
	}
}

void WinLoseMenu::render(sf::RenderTarget& target)
{
	target.draw(background);
	target.draw(container);

	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
	target.draw(this->menuText);
}