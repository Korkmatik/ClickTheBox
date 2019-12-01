#include "EnemyHandler.hpp"

EnemyHandler::EnemyHandler(sf::Vector2u screenWidth)
{
	numberEnemies = 1;

	this->screenDimension = new sf::Vector2u(screenWidth);
}

EnemyHandler::~EnemyHandler()
{
	// Clearing enemy types
	for (unsigned i = 0; i < enemyTypes.size(); i++) {
		delete enemyTypes[i];
	}
	enemyTypes.clear();

	// Clearing all active enemies
	for (unsigned i = 0; i < enemies.size(); i++) {
		delete enemies[i];
	}
	enemies.clear();
}

int EnemyHandler::isAnyEnemyHit(sf::Vector2f position) const
{
	for (unsigned int i = 0; i < enemies.size(); i++) {
		if (enemies[i]->doesIntersect(position)) {
			return i;
		}
	}

	return -1;
}

int EnemyHandler::getNumberActiveEnemies() const
{
	return enemies.size();
}

void EnemyHandler::spawnEnemy()
{
	int randomEnemyNumber = rand() % numberEnemies;

	switch (randomEnemyNumber) {
	case 0:
		spawnSimpleEnemy();
		break;
	default:
		printf("No such enemy: %d", randomEnemyNumber);
		break;
	}
}

void EnemyHandler::renderEnemies(sf::RenderTarget* target)
{
	for (unsigned i = 0; i < enemies.size(); i++) {
		enemies[i]->render(target);
	}
}

int EnemyHandler::updateEnemies()
{
	// Updating each Enemy
	for (unsigned i = 0; i < enemies.size(); i++) {
		enemies[i]->update();
	}

	int numberOutOfScreen = 0;

	std::vector<int> indexes;

	for (unsigned i = 0; i < enemies.size(); i++) {
		if (enemies[i]->isOutOfScreen()) {
			delete enemies[i];

			indexes.push_back(i);
		}
	}

	for (unsigned i = 0; i < indexes.size(); i++) {
		enemies.erase(enemies.begin() + indexes[i]);
	}

	return numberOutOfScreen;
}

void EnemyHandler::spawnSimpleEnemy()
{
	SimpleEnemy* enemy = new SimpleEnemy(*screenDimension);

	enemies.push_back(enemy);
}
