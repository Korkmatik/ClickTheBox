#pragma once

#include <vector>

#include "SimpleEnemy.hpp"

class EnemyHandler
{
public:
	EnemyHandler(sf::Vector2u screenWidth);
	virtual ~EnemyHandler();

	/*
		Checks if any enemy is hit

		Returns the first enemy index that was hit
	*/
	int isAnyEnemyHit(sf::Vector2f position) const;
	int getNumberActiveEnemies() const;

	void spawnEnemy();

	void renderEnemies(sf::RenderTarget* target);

	/*
		Updates all enemies on the scene

		Returns number of enemies that has reached out of screen
			if no enemy was hit then it returns -1
	*/
	int updateEnemies();

	/*
		Kills the enemy at the specified index

		Returns the enemy points
	*/
	int killEnemy(int index);
private:
	std::vector<BaseEnemy*> enemyTypes;
	std::vector<BaseEnemy*> enemies;

	sf::Vector2u* screenDimension;

	int numberEnemies;

	void spawnSimpleEnemy();
};

