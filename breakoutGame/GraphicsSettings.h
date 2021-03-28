#pragma once
/// <summary>
/// GraphicsSettings preservers information regarding 
/// window and graphics,like resolution ,video mode and 
/// frame rate of a window.
/// 
/// It is needed to INIT sf::RenderWindow.
/// 
/// </summary>
class GraphicsSettings
{
public:
	GraphicsSettings();

	//variables
	std::string title;
	sf::VideoMode resolution;
	bool fullscreen;
	bool vsync;
	unsigned frameRateLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;

	/// <summary>
	/// Saves variable information to a .ini file.
	/// </summary>
	/// <param name="path">-destination of .ini file with window config</param>
	void saveToFile(const std::string path);
	/// <summary>
	/// Reads variable information from a .ini file.
	/// </summary>
	/// <param name="path">-destination of .ini file with window config</param>
	void loadFromFile(const std::string path);

};
