#include "Hud.hpp"

Hud::Hud(sf::Vector2u screenDimension, int score, int health, int level)
	: BaseUI()
{
	this->screenDimension = new sf::Vector2u(screenDimension);

	this->score = score;
	this->health = health;
	this->level = level;

	initText();
}

void Hud::initText()
{
	int txtSize = 24;
	int marginTop = 8;
	float leftPos = 4.f;

	sf::Color txtColor = sf::Color::Red;

	scoreTxt = new sf::Text();
	scoreTxt->setFont(*font);
	scoreTxt->setString("Score: " + std::to_string(score));
	scoreTxt->setFillColor(txtColor);
	scoreTxt->setStyle(sf::Text::Bold);
	scoreTxt->setCharacterSize(txtSize);
	scoreTxt->setPosition(leftPos, 0.f);

	healthTxt = new sf::Text();
	healthTxt->setFont(*font);
	healthTxt->setString("Health: " + std::to_string(health));
	healthTxt->setFillColor(txtColor);
	healthTxt->setStyle(sf::Text::Bold);
	healthTxt->setCharacterSize(txtSize);
	healthTxt->setPosition(leftPos, static_cast<float>(txtSize + marginTop));

	levelTxt = new sf::Text();
	levelTxt->setFont(*font);
	levelTxt->setString("Level: " + std::to_string(level));
	levelTxt->setFillColor(txtColor);
	levelTxt->setStyle(sf::Text::Bold);
	levelTxt->setCharacterSize(txtSize);
	levelTxt->setPosition(leftPos, static_cast<float>((txtSize + marginTop) * 2));
}

Hud::~Hud()
{
	delete screenDimension;
	delete scoreTxt;
	delete healthTxt;
	delete levelTxt;
}

void Hud::updateScore(int score)
{
	scoreTxt->setString("Score: " + std::to_string(score));
}

void Hud::updateHealth(int health)
{
	healthTxt->setString("Health: " + std::to_string(health));
}

void Hud::udpateLevel(int level)
{
	levelTxt->setString("Level: " + std::to_string(level));
}

void Hud::render(sf::RenderTarget* target)
{
	target->draw(*healthTxt);
	target->draw(*scoreTxt);
	target->draw(*levelTxt);
}
