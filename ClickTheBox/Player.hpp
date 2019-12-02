#pragma once
class Player
{
public:
	Player(int startingHealth);

	int getHealth() const;
	void decreaseHealth();
	void increaseHealth();

	int getScore() const;
	void addToScore(int value);

private:
	int health;
	int score;
};

