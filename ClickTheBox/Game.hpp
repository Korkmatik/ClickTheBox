#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "EnemyHandler.hpp"
#include "Player.hpp"
#include "Hud.hpp"
#include "StartScreen.hpp"
#include "GameOverUI.hpp"

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
	StartScreen* startScreen;
	GameOverUI* gameOverScreen;

	bool isGameOver;
	bool doLevelIncrease;
	bool isGameInitialized;
	bool isGameStart;

	int maxEnemyCount;
	int levelNumber;
	sf::Time spawnInterval;
	sf::Time timeSinceLastSpawn;
	sf::Clock deltaClock;
	sf::Clock levelClock;
	sf::Clock backgroundClock;
	sf::Time timeToLevelUp;

	void initGame();
	void restartGame();

	void update();
	void spawnEnemyIfPossible();
	void increaseLevelIfPossible();
	
	void updatePlayerHealth();
	void updatePlayerScore(int points);
	
	void updateMousePosition();
	
	void checkIfGameOver();
	sf::Color getRandomBackGround();
	
	void increaseLevel();
	void updateLevel();
	bool isMaxLevelReached();
	
	void handlePollEvents();
	void handleMousePressedEvent();

	void updateGameObjects();
	void spawnEnemy();

	void render();
	void renderGame();
	void renderGameOverScreen();
	void renderGameObjects();

	void deleteGameObjects();
};

