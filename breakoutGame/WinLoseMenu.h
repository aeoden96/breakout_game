#pragma once
#include"libs.h"
#include "Gui.h"

class WinLoseMenu
{
private:
	sf::Font& font;
	sf::Text menuText;
	sf::RectangleShape background;
	sf::RectangleShape container;
	std::map<std::string, gui::Button*>  buttons;

	//Private functions

public:
	WinLoseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~WinLoseMenu();
	void setFinishScreen(gameState won_or_lost);
	//Accessor
	std::map<std::string, gui::Button*>& getButtons();

	//Functions
	const bool isButtonPressed(const std::string key);
	void pauseGraphics();
	void addButton(const std::string key, float y, const std::string text);
	void update(const sf::Vector2i& mousePosWindow);
	void render(sf::RenderTarget& target);
};
