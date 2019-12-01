#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "EnemyHandler.hpp"

class Game
{
	

public:
	Game();
	virtual ~Game();

	void start();
private:
	// Window specific attributes
	sf::RenderWindow* window;
	sf::Event* sfEvent;

	sf::Vector2f mousePosition;
	
	EnemyHandler* enemyHandler;

	// Game logic attributes
	bool isGameOver;
	bool doLevelIncrease;
	int maxEnemyCount;
	sf::Time spawnInterval;
	sf::Time timeSinceLastSpawn;
	sf::Clock deltaClock;
	sf::Clock gameClock;
	sf::Time timeToLevelUp;

	void update();
	void handlePollEvents();
	void updateGameObjects();
	void spawnEnemy();

	void render();
	void renderGameObjects();
};

