#pragma once

#include <SFML/Graphics.hpp>

class Hud
{
public:
	Hud(sf::Vector2u screenDimension,
		int score,
		int health,
		int level
	);
	virtual ~Hud();

	void updateScore(int score);
	void updateHealth(int health);
	void udpateLevel(int level);

	void render(sf::RenderTarget* target);

private:
	sf::Vector2u* screenDimension;
	sf::Font* font;

	sf::Text* scoreTxt;
	sf::Text* healthTxt;
	sf::Text* levelTxt;
	
	void initFont();
	void initText(int score, int health, int level);
};

