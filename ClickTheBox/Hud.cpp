#include "Hud.hpp"

Hud::Hud(sf::Vector2u screenDimension, int score, int health, int level)
	: score(score), health(health), level(level)
{
	this->screenDimension = new sf::Vector2u(screenDimension);

	font = new sf::Font();
	if (!font->loadFromFile("arial.ttf")) {
		throw std::invalid_argument("Could not load Font: arial.ttf");
	}

	int txtSize = 24;
	sf::Color txtColor = sf::Color::Red;

	scoreTxt = new sf::Text();
	scoreTxt->setFont(*font);
	scoreTxt->setString("Score: " + std::to_string(score));
	scoreTxt->setFillColor(txtColor);
	scoreTxt->setStyle(sf::Text::Bold);
	scoreTxt->setCharacterSize(txtSize);
	scoreTxt->setPosition(0.f, 0.f);

	healthTxt = new sf::Text();
	healthTxt->setFont(*font);
	healthTxt->setString("Health: " + std::to_string(health));
	healthTxt->setFillColor(txtColor);
	healthTxt->setStyle(sf::Text::Bold);
	healthTxt->setCharacterSize(txtSize);
	healthTxt->setPosition(0.f, static_cast<float>(txtSize + 5));

	levelTxt = new sf::Text();
	levelTxt->setFont(*font);
	levelTxt->setString("Level: " + std::to_string(level));
	levelTxt->setFillColor(txtColor);
	levelTxt->setStyle(sf::Text::Bold);
	levelTxt->setCharacterSize(txtSize);
	levelTxt->setPosition(0.f, static_cast<float>(txtSize * 2 + 5));
}

Hud::~Hud()
{
	delete screenDimension;
	delete font;
	delete scoreTxt;
	delete healthTxt;
	delete levelTxt;
}

void Hud::updateScore(int score)
{
	this->score = score;
}

void Hud::updateHealth(int health)
{
	this->health = health;
}

void Hud::udpateLevel(int level)
{
	this->level = level;
}

void Hud::render(sf::RenderTarget* target)
{
	target->draw(*healthTxt);
	target->draw(*scoreTxt);
	target->draw(*levelTxt);
}
