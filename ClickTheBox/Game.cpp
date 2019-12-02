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

	player = new Player(10);
	isGameOver = false;
	levelNumber = 0;
	maxEnemyCount = 10;
	spawnInterval = sf::milliseconds(1500);
	timeSinceLastSpawn = spawnInterval;
	timeToLevelUp = sf::seconds(2);
	doLevelIncrease = true;

	enemyHandler = new EnemyHandler(window->getSize());
}

Game::~Game()
{
	delete window;
	delete sfEvent;
	delete player;
}

void Game::start()
{
	levelClock.restart();

	while (!isGameOver)
	{
		update();
		render();
	}
}

void Game::update()
{
	handlePollEvents();
	updateGameObjects();

	mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		int enemyIndex = enemyHandler->isAnyEnemyHit(mousePosition);
		if (enemyIndex != -1) {
			player->increaseHealth();
			int points = enemyHandler->killEnemy(enemyIndex);
			player->addToScore(points);

			std::cout << "Score: " << player->getScore() << "\n";
			std::cout << "Health: " << player->getHealth() << "\n" << std::endl;
		}
	}

	// Spawning Enemies
	if (timeSinceLastSpawn >= spawnInterval) {
		spawnEnemy();
		timeSinceLastSpawn = sf::milliseconds(0);
	}
	else {
		timeSinceLastSpawn += sf::milliseconds(deltaClock.restart().asMilliseconds());
	}

	
	if (doLevelIncrease) {
		increaseLevel();
	}
	
}

void Game::increaseLevel()
{
	if (levelClock.getElapsedTime().asMilliseconds() >= timeToLevelUp.asMilliseconds()) {
		int newMillis = spawnInterval.asMilliseconds() - 100;
		spawnInterval = sf::milliseconds(newMillis);
		maxEnemyCount += 1;
		levelNumber += 1;
		levelClock.restart();

		std::cout << "Level: " << levelNumber << "\n";
	}

	if (isMaxLevelReached()) {
		doLevelIncrease = false;
	}
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
			window->close();
			isGameOver = true;
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

	window->display();
}

void Game::renderGameObjects()
{
	enemyHandler->renderEnemies(window);
}
