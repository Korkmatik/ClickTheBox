#pragma once

#include <SFML/Graphics.hpp>

class StartScreen
{
public:
	StartScreen(sf::Vector2u screenDimensions);
	virtual ~StartScreen();

private:
	sf::Vector2u* screenDimensions;

	sf::Font* font;
	sf::Text* text;
};

