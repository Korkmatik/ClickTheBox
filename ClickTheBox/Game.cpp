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

	isGameOver = false;
	maxEnemyCount = 10;
	spawnInterval = sf::milliseconds(1500);
	timeSinceLastSpawn = spawnInterval;
	timeToLevelUp = sf::milliseconds(2000);
	doLevelIncrease = true;

	enemyHandler = new EnemyHandler(window->getSize());
}

Game::~Game()
{
	delete window;
	delete sfEvent;
}

void Game::start()
{
	gameClock.restart();

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
		if (enemyHandler->isAnyEnemyHit(mousePosition) != -1) {
			std::cout << "Click in enemy\n";
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
		// Increasing level
		if (static_cast<int>(gameClock.getElapsedTime().asMilliseconds()) >= static_cast<int>(timeToLevelUp.asMilliseconds())) {
			int newMillis = static_cast<int>(spawnInterval.asMilliseconds()) - 100;
			spawnInterval = sf::milliseconds(newMillis);
			maxEnemyCount += 1;
		}

		if (static_cast<int>(spawnInterval.asMilliseconds()) <= 300) {
			doLevelIncrease = false;
		}
	}
	
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
	enemyHandler->updateEnemies();
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
