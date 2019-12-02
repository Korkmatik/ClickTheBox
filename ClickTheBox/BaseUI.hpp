#pragma once

#include <SFML/Graphics.hpp>

class BaseUI
{
public:
	BaseUI();
	virtual ~BaseUI();

protected:
	sf::Font* font;

	virtual void initText() = 0;

private:
	void initFont();
};

