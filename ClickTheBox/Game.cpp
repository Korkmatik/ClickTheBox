#include "Game.hpp"

#include <iostream>

Game::Game()
{
	window = new sf::RenderWindow(
		sf::VideoMode(800, 600), 
		"Click the Box", 
		sf::Style::Default
	);
	window->setFramerateLimit(60);

	sfEvent = new sf::Event();

	isGameOver = false;

	enemyHandler = new EnemyHandler(window->getSize());
}

Game::~Game()
{
	delete window;
	delete sfEvent;
}

void Game::start()
{
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
