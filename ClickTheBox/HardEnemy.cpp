#include "HardEnemy.h"

HardEnemy::HardEnemy(sf::Vector2u screenDimensions)
	: BaseEnemy(20, screenDimensions)
{
	shape = new sf::CircleShape();
	shape->setFillColor(sf::Color::Red);
	shape->setRadius(12.f);

	float size = shape->getRadius() * 2;
	auto position = generateRandomPosition(size, size);
	shape->setPosition(*position);
	delete position;

	speed = 6.5f;
}

HardEnemy::~HardEnemy()
{
	delete shape;
}

void HardEnemy::render(sf::RenderTarget* target) const
{
	target->draw(*shape);
}

void HardEnemy::update()
{
	shape->move(0.f, speed);
}

bool HardEnemy::isOutOfScreen() const
{
	return BaseEnemy::isOutOfScreen(shape->getPosition());
}

bool HardEnemy::doesIntersect(sf::Vector2f position) const
{
	bool doesIntersect = shape->getGlobalBounds().contains(position);
	return doesIntersect;
}
