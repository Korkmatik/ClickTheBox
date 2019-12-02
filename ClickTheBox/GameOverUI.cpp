#include "GameOverUI.hpp"


GameOverUI::GameOverUI(sf::Vector2u screenDimension)
	: BaseUI()
{
	this->screenDimension = new sf::Vector2u(screenDimension);

	initText();
}

GameOverUI::~GameOverUI()
{
	delete gameOverTxt;
	delete screenDimension;
}

void GameOverUI::render(sf::RenderTarget* target)
{
	target->draw(*gameOverTxt);
	target->draw(*restartGameTxt);
}

void GameOverUI::setScore(int score)
{
	std::string message = "Game Over! Your Score: " + std::to_string(score);
	gameOverTxt->setString(message);
}

void GameOverUI::initText()
{
	int characterSize = 32;
	sf::Color fillColor = sf::Color::Red;
	sf::Uint32 style = sf::Text::Bold;
	sf::Vector2f positionGameOver(
		20.f,
		screenDimension->y / 2 - characterSize / 2
	);

	gameOverTxt = new sf::Text();

	gameOverTxt->setFont(*font);
	gameOverTxt->setCharacterSize(characterSize);
	gameOverTxt->setFillColor(fillColor);
	gameOverTxt->setStyle(style);
	gameOverTxt->setPosition(positionGameOver);

	sf::Vector2f positionRestartTxt(
		20.f,
		screenDimension->y / 2 + characterSize * 2
	);

	restartGameTxt = new sf::Text();

	restartGameTxt->setFont(*font);
	restartGameTxt->setCharacterSize(characterSize / 2);
	restartGameTxt->setFillColor(sf::Color::Magenta);
	restartGameTxt->setStyle(style);
	restartGameTxt->setPosition(positionRestartTxt);
	restartGameTxt->setString("Press Right Mouse Button To Restart!");
}