#pragma once

#include "BaseUI.hpp"

class StartScreen : public BaseUI
{
public:
	StartScreen(sf::Vector2u screenDimensions);
	virtual ~StartScreen();

	virtual void render(sf::RenderTarget* target) override;
private:
	sf::Vector2u* screenDimensions;

	sf::Text* text;

	virtual void initText() override;
};

