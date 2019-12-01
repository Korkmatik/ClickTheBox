#pragma once

#include "BaseEnemy.hpp"

class SimpleEnemy : public BaseEnemy
{
public:
	SimpleEnemy(sf::Vector2u screenDimension);
	virtual ~SimpleEnemy();

	// Inherited via BaseEnemy
	virtual void update() override;

	// Inherited via BaseEnemy
	virtual void render(sf::RenderTarget* target) const override;
	virtual bool isOutOfScreen() const override;

	virtual bool doesIntersect(sf::Vector2f position) const override;

private:
	sf::RectangleShape* shape;

	const sf::Vector2u* screenDimension;
};

