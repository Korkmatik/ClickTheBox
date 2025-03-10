#include "EnemyHandler.hpp"

#include <string>

EnemyHandler::EnemyHandler(sf::Vector2u screenWidth)
{
	numberEnemies = 3;

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

void EnemyHandler::spawnEnemy(int level)
{
	int numberSpawnableEnemies = 1;

	if (level >= 10) {
		numberSpawnableEnemies = 3;
	}
	else if (level >= 5) {
		numberSpawnableEnemies = 2;
	}

	if (numberSpawnableEnemies > numberEnemies) {
		numberSpawnableEnemies = numberEnemies;
	}

	int randomEnemyNumber = rand() % numberSpawnableEnemies;

	switch (randomEnemyNumber) {
	case 0:
		spawnSimpleEnemy();
		break;
	case 1:
		spawnMediumEnemy();
		break;
	case 2:
		spawnHardEnemy();
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
	updateEachEnemy();

	int numberOutOfScreen = deleteEnemiesThatAreOutOfScreen();

	return numberOutOfScreen;
}

void EnemyHandler::updateEachEnemy()
{
	for (unsigned i = 0; i < enemies.size(); i++) {
		enemies[i]->update();
	}
}

int EnemyHandler::deleteEnemiesThatAreOutOfScreen()
{
	int numberOutOfScreen = 0;

	for (unsigned i = 0; i < enemies.size();) {
		if (enemies[i]->isOutOfScreen()) {
			delete enemies[i];

			enemies.erase(enemies.begin() + i);

			numberOutOfScreen += 1;
			continue;
		}
		i++;

		if (i >= enemies.size()) {
			break;
		}
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

void EnemyHandler::spawnMediumEnemy()
{
	MediumEnemy* enemy = new MediumEnemy(*screenDimension);

	enemies.push_back(enemy);
}

void EnemyHandler::spawnHardEnemy()
{
	HardEnemy* enemy = new HardEnemy(*screenDimension);
	enemies.push_back(enemy);
}
