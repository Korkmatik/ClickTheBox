#include "BaseEnemy.hpp"


BaseEnemy::BaseEnemy(int points, sf::Vector2u screenDimensions)
{
	this->points = points;

	this->screenDimensions = new sf::Vector2u(screenDimensions);
}

BaseEnemy::~BaseEnemy()
{
	delete screenDimensions;
}

bool BaseEnemy::isOutOfScreen(const sf::Vector2f& const shapePosition) const
{
	bool isOutOfScreen = false;

	if (shapePosition.x > screenDimensions->x ||
		shapePosition.y > screenDimensions->y) {
		isOutOfScreen = true;
	}

	return isOutOfScreen;
}

int BaseEnemy::getPoints() const
{
	return points;
}

sf::Vector2f* BaseEnemy::generateRandomPosition(float shapeWidth, float shapeHeight)
{
	sf::Vector2f* randomPos = new sf::Vector2f();
	randomPos->x = float(rand() % int(screenDimensions->x - shapeWidth));
	randomPos->y = 0.f - shapeHeight;

	return randomPos;
}