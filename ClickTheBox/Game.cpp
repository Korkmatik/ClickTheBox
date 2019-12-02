#include "Game.hpp"

#include <iostream>

Game::Game()
{
	srand(static_cast<unsigned>(time(NULL)));

	window = new sf::RenderWindow(
		sf::VideoMode(800, 600), 
		"Click the Box", 
		sf::Style::Default
	);
	window->setFramerateLimit(60);

	sfEvent = new sf::Event();

	isGameInitialized = false;

	initGame();
}

void Game::initGame()
{
	if (isGameInitialized)
		return;

	player = new Player(10);
	isGameOver = false;
	levelNumber = 1;
	maxEnemyCount = 10;
	spawnInterval = sf::milliseconds(1500);
	timeSinceLastSpawn = spawnInterval;
	timeToLevelUp = sf::seconds(2);
	doLevelIncrease = true;

	enemyHandler = new EnemyHandler(window->getSize());

	hud = new Hud(
		window->getSize(),
		player->getScore(),
		player->getHealth(),
		levelNumber
	);

	isGameInitialized = true;
}

void Game::restartGame()
{
	deleteGameObjects();
	initGame();
}

Game::~Game()
{
	delete window;
	delete sfEvent;
	deleteGameObjects();
}

void Game::deleteGameObjects()
{
	if (isGameInitialized) {
		delete player;
		delete hud;
		delete enemyHandler;

		isGameInitialized = false;
	}
	
}

void Game::start()
{
	levelClock.restart();

	while (!isGameOver && window->isOpen())
	{
		update();
		render();
	}

	#ifdef _DEBUG
		std::cout << "Game Over" << std::endl;
	#endif // _DEBUG
}

void Game::update()
{
	updateMousePosition();

	handlePollEvents();
	updateGameObjects();

	spawnEnemyIfSpawnable();
	
	increaseLevelIfPossible();
	
	checkIfGameOver();
}

void Game::spawnEnemyIfSpawnable()
{
	if (timeSinceLastSpawn >= spawnInterval) {
		spawnEnemy();
		timeSinceLastSpawn = sf::milliseconds(0);
	}
	else {
		timeSinceLastSpawn += sf::milliseconds(deltaClock.restart().asMilliseconds());
	}
}

void Game::increaseLevelIfPossible()
{
	if (doLevelIncrease) {
		increaseLevel();
	}
}

void Game::handleMousePressedEvent()
{
	int enemyIndex = enemyHandler->isAnyEnemyHit(mousePosition);
	if (enemyIndex != -1) {
		int points = enemyHandler->killEnemy(enemyIndex);
			
		updatePlayerHealth();
		updatePlayerScore(points);

		#ifdef _DEBUG
			std::cout << "Score: " << player->getScore() << "\n";
			std::cout << "Health: " << player->getHealth() << "\n" << std::endl;
		#endif // _DEBUG
		}
}

void Game::updatePlayerHealth()
{
	player->increaseHealth();
	hud->updateHealth(player->getHealth());
}

void Game::updatePlayerScore(int points)
{
	player->addToScore(points);
	hud->updateScore(player->getScore());
}

void Game::updateMousePosition()
{
	mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}

void Game::checkIfGameOver()
{
	if (player->isDead()) {
		isGameOver = true;
	}
}

void Game::increaseLevel()
{
	if (levelClock.getElapsedTime().asMilliseconds() >= timeToLevelUp.asMilliseconds()) {
		int newMillis = spawnInterval.asMilliseconds() - 100;
		spawnInterval = sf::milliseconds(newMillis);
		maxEnemyCount += 1;
		levelClock.restart();

		updateLevel();
#ifdef _DEBUG
		std::cout << "Level: " << levelNumber << "\n";
#endif // _DEBUG		
	}

	if (isMaxLevelReached()) {
		doLevelIncrease = false;
	}
}

void Game::updateLevel()
{
	levelNumber += 1;
	hud->udpateLevel(levelNumber);
}

bool Game::isMaxLevelReached()
{
	return static_cast<int>(spawnInterval.asMilliseconds()) <= 300;
}

void Game::handlePollEvents()
{
	while (window->pollEvent(*sfEvent))
	{
		if (sfEvent->type == sf::Event::Closed) {
			isGameOver = true;
			window->close();
		}
		if (sfEvent->mouseButton.button == sf::Mouse::Left) {
			handleMousePressedEvent();
		}
	}
}

void Game::updateGameObjects()
{
	int numberEnemiesOutOfScreen = enemyHandler->updateEnemies();
	player->decreaseHealth(numberEnemiesOutOfScreen);
}

void Game::spawnEnemy()
{
	if (enemyHandler->getNumberActiveEnemies() < maxEnemyCount) {
		enemyHandler->spawnEnemy();
	}
}

void Game::render()
{
	window->clear();

	renderGameObjects();

	hud->render(window);

	window->display();
}

void Game::renderGameObjects()
{
	enemyHandler->renderEnemies(window);
}
