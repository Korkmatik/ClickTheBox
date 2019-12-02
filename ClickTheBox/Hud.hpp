#pragma once

#include "BaseUI.hpp"

class Hud : public BaseUI
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

	virtual void render(sf::RenderTarget* target) override;

private:
	sf::Vector2u* screenDimension;

	sf::Text* scoreTxt;
	sf::Text* healthTxt;
	sf::Text* levelTxt;

	int score, health, level;
	
	virtual void initText() override;
};

