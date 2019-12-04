#include "Player.hpp"

#include <iostream>
#include <fstream>

Player::Player(int startingHealth)
{
	health = startingHealth;
	score = 0;

	loadHighScoreFromFile();
}

Player::~Player()
{
	try {
		std::ofstream file("highscore.txt");

		file << highscore;

		printf("Highscore saved\n");
	}
	catch (std::exception & e) {
		printf("Highscore could not be saved!\n");
		printf("Fehler: %s\n", e.what());
	}
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

	if (score > highscore) {
		highscore = score;
		printf("New Highscore: %d\n", highscore);
	}
}

int Player::getHighscore() const
{
	return highscore;
}

void Player::loadHighScoreFromFile()
{
	try {
		std::ifstream file;
		file.open("highscore.txt");

		file >> highscore;

		file.close();

		printf("Highscore loaded\n");
		printf("Highscore: %d\n", highscore);
	} catch (std::exception & e) {
		printf("Fehler: %s\n", e.what());
		highscore = 0;
	}
}
