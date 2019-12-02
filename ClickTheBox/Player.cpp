#include "Player.hpp"

Player::Player(int startingHealth)
{
	health = startingHealth;
	score = 0;
}

bool Player::isDead() const
{
	return health <= 0;
}

int Player::getHealth() const
{
	return health;
}

void Player::decreaseHealth(int amount)
{
	health -= amount;
}

void Player::increaseHealth()
{
	health += 1;
}

int Player::getScore() const
{
	return score;
}

void Player::addToScore(int value)
{
	if (value <= 0) {
		return;
	}

	score += value;
}
