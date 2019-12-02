#pragma once

#include "BaseUI.hpp"

class GameOverUI : public BaseUI
{
public:
	GameOverUI(sf::Vector2u screenDimension);
	virtual ~GameOverUI();

	virtual void render(sf::RenderTarget* target) override;

	void setScore(int score);
private:
	sf::Text* gameOverTxt;
	sf::Vector2u* screenDimension;

	int score;

	virtual void initText() override;
};

