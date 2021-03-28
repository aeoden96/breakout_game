#pragma once

#include "libs.h"
#include "GraphicsSettings.h"
#include "State.h"

class Game
{
private:


	//Variables

	/// <summary>
	/// Preserves important window settings.
	/// </summary>
	GraphicsSettings gfxSettings;
	StateData stateData;

	sf::Event sfEvent;
	sf::Clock dtClock;

	sf::RenderWindow* window;
	std::stack<State*> states;

	float dt;
	float gridSize;

	/// <summary>
	/// Map of all available keys that can be used.
	/// Key is a string that represents a key,
	/// and key_value is actual value of that key on the keyboard.
	/// </summary>
	std::map<std::string, int > supportedKeys;

	//Initialization

	/// <summary>
	/// Inits window pointer, gridSize and dt.
	/// </summary>
	void initVariables();

	/// <summary>
	/// Initializes gfxSettings object,using info from .ini file.
	/// </summary>
	void initGraphicsSettings();

	void initStateData();
	void initWindow();
	void initStates();

	/// <summary>
	/// Inits keys from Config/supportedKeys.ini
	/// and maps them key => key_value.  
	/// ex: A -> 0
	/// </summary>
	void initKeys();
public:

	//Constructors/Destructors
	Game();
	~Game();


	//Functions

	//Regular
	void endApplication();

	//Update
	void updateDt();
	void update();
	void updateSFMLEvents();

	//Render
	void render();

	//Core
	void run();

};


