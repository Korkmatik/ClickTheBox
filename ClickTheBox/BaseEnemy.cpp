#include "BaseEnemy.hpp"


BaseEnemy::BaseEnemy(sf::RectangleShape* shape, int points, float velocity, sf::Vector2f* screenDimensions)
{
	this->position = generateRandomPosition(screenDimensions->x);

	this->screenDimensions = screenDimensions;
	this->points = points;
	this->velocityY = velocity;
	this->shape = shape;
}

BaseEnemy::~BaseEnemy()
{
	delete position;
}

void BaseEnemy::render(sf::RenderTarget* target) const
{
	target->draw(*shape);
}

void BaseEnemy::update()
{
	move();
}

bool BaseEnemy::isOutOfScreen() const
{
	bool isOutOfScreen = false;
	const sf::Vector2f currentPosition = shape->getPosition();

	if (currentPosition.x > screenDimensions->x ||
		currentPosition.y > screenDimensions->y) {
		isOutOfScreen = true;
	}

	return isOutOfScreen;
}

sf::Vector2f* BaseEnemy::generateRandomPosition(int screenWidth)
{
	sf::Vector2f* randomPos = new sf::Vector2f();
	randomPos->x = rand() % (screenWidth);
	randomPos->y = 0.f;

	return randomPos;
}

void BaseEnemy::move()
{
	shape->move(0.f, velocityY);
}