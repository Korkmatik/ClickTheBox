#include "StartScreen.hpp"

StartScreen::StartScreen(sf::Vector2u screenDimensions)
{
	this->screenDimensions = new sf::Vector2u(screenDimensions);


}

StartScreen::~StartScreen()
{
	delete screenDimensions;
}
