#pragma once

#include <SFML/Graphics.hpp>

class BaseEnemy
{
public:
	BaseEnemy(int points, sf::Vector2u screenDimensions);
	virtual ~BaseEnemy();

	virtual void render(sf::RenderTarget* target) const = 0;
	virtual void update() = 0;

	virtual bool isOutOfScreen() const = 0;
	virtual int getPoints() const;
	virtual bool doesIntersect(sf::Vector2f position) const = 0;

	
protected:
	virtual sf::Vector2f* generateRandomPosition(float shapeWidth, float shapeHeight);
	virtual bool isOutOfScreen(const sf::Vector2f& const shapePosition) const;

private:	
	int points;

	sf::Vector2u* screenDimensions;
};

