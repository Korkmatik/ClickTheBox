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

	circle = new sf::CircleShape(100.f);
	circle->setFillColor(sf::Color::Green);

	isGameOver = false;

	enemy = new SimpleEnemy(window->getSize());
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
	//std::cout << "Mouse: " << mousePosition.x << " " << mousePosition.y << "\n";

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (enemy->doesIntersect(mousePosition)) {
			std::cout << "Click in enemy\n";
		}
	}
}

void Game::handlePollEvents()
{
	while (window->pollEvent(*sfEvent))
	{
		if (sfEvent->type == sf::Event::Closed)
			window->close();
	}
}

void Game::updateGameObjects()
{
	enemy->update();
}

void Game::render()
{
	window->clear();

	renderGameObjects();

	window->display();
}

void Game::renderGameObjects()
{
	window->draw(*circle);

	enemy->render(window);
}
