#pragma once

#include <SFML/Graphics.hpp>

class BaseEnemy
{
public:
	BaseEnemy(int points, sf::Vector2f screenDimensions);
	virtual ~BaseEnemy();

	virtual void render(sf::RenderTarget* target) const = 0;
	virtual void update() = 0;

	virtual bool isOutOfScreen() const = 0;
	virtual int getPoints() const;

	static sf::Vector2f* generateRandomPosition(int screenWidth);

protected:
	virtual bool isOutOfScreen(sf::Vector2f& shapePosition) const;

private:	
	int points;

	sf::Vector2f* screenDimensions;
};

