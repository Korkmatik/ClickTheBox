#pragma once
class Player
{
public:
	Player(int startingHealth);

	bool isDead() const;

	int getHealth() const;
	void decreaseHealth(int amount);
	void increaseHealth();

	int getScore() const;
	void addToScore(int value);

private:
	int health;
	int score;
};

