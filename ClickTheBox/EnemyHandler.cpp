#include "EnemyHandler.hpp"

EnemyHandler::EnemyHandler( sf::Vector2u screenWidth)
{
	enemyTypes.push_back(new SimpleEnemy(screenWidth));
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

void EnemyHandler::spawnEnemy()
{
}

void EnemyHandler::renderEnemies(sf::RenderTarget* target)
{
	for (unsigned i = 0; i < enemies.size(); i++) {
		enemies[i]->render(target);
	}
}

int EnemyHandler::updateEnemies()
{
	int numberOutOfScreen = 0;

	for (auto it = enemies.begin(); it != enemies.end(); it++) {
		(*it)->update();

		if ((*it)->isOutOfScreen()) {
			delete* it;
			enemies.erase(it);

			numberOutOfScreen += 1;
		}
	}

	return numberOutOfScreen;
}
