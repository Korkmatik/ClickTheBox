#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "EnemyHandler.hpp"
#include "Player.hpp"

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
	Player* player;
	bool isGameOver;
	bool doLevelIncrease;
	int maxEnemyCount;
	int levelNumber;
	sf::Time spawnInterval;
	sf::Time timeSinceLastSpawn;
	sf::Clock deltaClock;
	sf::Clock levelClock;
	sf::Time timeToLevelUp;

	void update();
	void increaseLevel();
	bool isMaxLevelReached();
	void handlePollEvents();
	void updateGameObjects();
	void spawnEnemy();

	void render();
	void renderGameObjects();
};

