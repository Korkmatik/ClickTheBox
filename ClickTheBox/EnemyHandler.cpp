#include "EnemyHandler.hpp"

#include <string>

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

			numberOutOfScreen += 1;
		}
	}

	for (unsigned i = 0; i < indexes.size(); i++) {
		enemies.erase(enemies.begin() + indexes[i]);
	}

	return numberOutOfScreen;
}

int EnemyHandler::killEnemy(int index)
{
	if (index < 0 || static_cast<unsigned>(index) >= enemies.size()) {
		std::string exceptionStr = "There is no enemy with the index " + std::to_string(index);
		throw std::invalid_argument(exceptionStr.c_str());
	}

	int points = enemies[index]->getPoints();

	delete enemies[index];
	enemies.erase(enemies.begin() + index);

	return points;
}

void EnemyHandler::spawnSimpleEnemy()
{
	SimpleEnemy* enemy = new SimpleEnemy(*screenDimension);

	enemies.push_back(enemy);
}
