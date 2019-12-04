#pragma once

#include "BaseUI.hpp"

class GameOverUI : public BaseUI
{
public:
	GameOverUI(sf::Vector2u screenDimension);
	virtual ~GameOverUI();

	virtual void render(sf::RenderTarget* target) override;

	void setScore(int score);
	void setHighscore(int highscore);
private:
	sf::Text* gameOverTxt;
	sf::Text* highscoreTxt;
	sf::Text* restartGameTxt;
	sf::Vector2u* screenDimension;

	int score, highscore;

	virtual void initText() override;
};

