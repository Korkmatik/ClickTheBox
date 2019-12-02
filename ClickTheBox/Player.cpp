#include "Player.hpp"

Player::Player(int startingHealth)
{
	health = startingHealth;
	score = 0;
}

int Player::getHealth() const
{
	return health;
}

void Player::decreaseHealth()
{
	health -= 1;
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
