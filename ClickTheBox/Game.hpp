#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "EnemyHandler.hpp"
#include "Player.hpp"
#include "Hud.hpp"

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
	Hud* hud;
	bool isGameOver;
	bool doLevelIncrease;
	bool isGameInitialized;
	int maxEnemyCount;
	int levelNumber;
	sf::Time spawnInterval;
	sf::Time timeSinceLastSpawn;
	sf::Clock deltaClock;
	sf::Clock levelClock;
	sf::Time timeToLevelUp;

	void initGame();
	void restartGame();

	void update();
	void spawnEnemyIfSpawnable();
	void increaseLevelIfPossible();
	void handleMousePressedEvent();
	void updatePlayerHealth();
	void updatePlayerScore(int points);
	void updateMousePosition();
	void checkIfGameOver();
	void increaseLevel();
	void updateLevel();
	bool isMaxLevelReached();
	void handlePollEvents();
	void updateGameObjects();
	void spawnEnemy();

	void render();
	void renderGameObjects();

	void deleteGameObjects();
};

