#include "StartScreen.hpp"

StartScreen::StartScreen(sf::Vector2u screenDimensions)
	: BaseUI()
{
	this->screenDimensions = new sf::Vector2u(screenDimensions);

	initText();
}

StartScreen::~StartScreen()
{
	delete text;
	delete screenDimensions;
}

void StartScreen::initText()
{
	int characterSize = 64;
	sf::Color fillColor = sf::Color::Blue;
	sf::Uint32 style = sf::Text::Bold;
	sf::Vector2f position(
		5.f,
		screenDimensions->y / 2 - characterSize / 2
	);

	text = new sf::Text();

	text->setFont(*font);

	text->setString("Click on the Screen to start the Game!");
	text->setCharacterSize(characterSize);
	text->setFillColor(fillColor);
	text->setStyle(style);
	text->setPosition(position);
}

void StartScreen::render(sf::RenderTarget* target)
{
	target->draw(*text);
}
