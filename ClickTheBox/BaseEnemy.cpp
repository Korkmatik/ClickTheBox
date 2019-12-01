#include "BaseEnemy.hpp"


BaseEnemy::BaseEnemy(int points, sf::Vector2f screenDimensions)
{
	this->points = points;

	this->screenDimensions = new sf::Vector2f(screenDimensions);
}

BaseEnemy::~BaseEnemy()
{
	delete screenDimensions;
}

bool BaseEnemy::isOutOfScreen(sf::Vector2f& shapePosition) const
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

sf::Vector2f* BaseEnemy::generateRandomPosition(int screenWidth)
{
	sf::Vector2f* randomPos = new sf::Vector2f();
	randomPos->x = int(rand() % (screenWidth));
	randomPos->y = 0.f;

	return randomPos;
}