#include "SimpleEnemy.hpp"


SimpleEnemy::SimpleEnemy(sf::Vector2u screenDimension) :
	BaseEnemy(5, screenDimension)
{
	this->screenDimension = new sf::Vector2u(screenDimension);

	shape = new sf::RectangleShape();
	shape->setFillColor(sf::Color::Green);
	shape->setSize(sf::Vector2f(40.f, 40.f));

	sf::Vector2f* randomPosition = generateRandomPosition(shape->getSize().x, shape->getSize().y);

	shape->setPosition(*randomPosition);

	delete randomPosition;
}

SimpleEnemy::~SimpleEnemy()
{
	delete screenDimension;
	delete shape;
}

void SimpleEnemy::update()
{
	shape->move(0, 5.f);
}

void SimpleEnemy::render(sf::RenderTarget* target) const
{
	target->draw(*shape);
}

bool SimpleEnemy::isOutOfScreen() const
{
	return BaseEnemy::isOutOfScreen(shape->getPosition());
}

bool SimpleEnemy::doesIntersect(sf::Vector2f position) const
{
	bool doesIntersect = shape->getGlobalBounds().contains(position);

	return doesIntersect;
}
