#pragma once

#include "BaseEnemy.hpp"

class HardEnemy : public BaseEnemy
{
public:
	HardEnemy(sf::Vector2u screenDimensions);
	virtual ~HardEnemy();

	// Inherited via BaseEnemy
	virtual void render(sf::RenderTarget* target) const override;
	virtual void update() override;
	virtual bool isOutOfScreen() const override;
	virtual bool doesIntersect(sf::Vector2f position) const override;

private:
	sf::CircleShape* shape;

	float speed;
};

