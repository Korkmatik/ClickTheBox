#pragma once

#include "BaseEnemy.hpp"

class MediumEnemy : public BaseEnemy
{
public:
	MediumEnemy(sf::Vector2u screenDimensions);
	virtual ~MediumEnemy();

	virtual void render(sf::RenderTarget* target) const override;
	virtual void update() override;

	virtual bool isOutOfScreen() const override;
	virtual bool doesIntersect(sf::Vector2f position) const override;

private:
	sf::RectangleShape* shape;

	float speed;
};

