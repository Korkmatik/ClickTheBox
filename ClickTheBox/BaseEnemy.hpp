#pragma once

#include <SFML/Graphics.hpp>

class BaseEnemy
{
public:
	BaseEnemy(sf::RectangleShape* shape, int points, float velocityY, sf::Vector2f* screenDimensions);
	virtual ~BaseEnemy();

	virtual void render(sf::RenderTarget* target) const;
	virtual void update();

	virtual bool isOutOfScreen() const;

	static sf::Vector2f* generateRandomPosition(int screenWidth);
private:
	float velocityY;
	sf::Vector2f* position;

	sf::RectangleShape* shape;

	sf::Vector2f* screenDimensions;
	
	int points;

	virtual void move();
};

