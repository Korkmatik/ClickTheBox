#include "MediumEnemy.hpp"

MediumEnemy::MediumEnemy(sf::Vector2u screenDimensions)
	: BaseEnemy(10, screenDimensions)
{
	shape = new sf::RectangleShape();
	shape->setFillColor(sf::Color::Magenta);
	shape->setSize(sf::Vector2f(30.f, 30.f));
	
	sf::Vector2f* position = generateRandomPosition(shape->getSize().x, shape->getSize().y);
	shape->setPosition(*position);
	delete position;

	speed = 5.f;
}

MediumEnemy::~MediumEnemy()
{
	delete shape;
}

void MediumEnemy::render(sf::RenderTarget* target) const
{
	target->draw(*shape);
}

void MediumEnemy::update()
{
	shape->move(0.f, speed);
}

bool MediumEnemy::isOutOfScreen() const
{
	return BaseEnemy::isOutOfScreen(shape->getPosition());
}

bool MediumEnemy::doesIntersect(sf::Vector2f position) const
{
	bool doesIntersect = shape->getGlobalBounds().contains(position);
	return doesIntersect;
}
