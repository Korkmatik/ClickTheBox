#include "Game.hpp"

Game::Game()
{
	window = new sf::RenderWindow(
		sf::VideoMode(800, 600), 
		"Click the Box", 
		sf::Style::Default
	);
	sfEvent = new sf::Event();

	circle = new sf::CircleShape(100.f);
	circle->setFillColor(sf::Color::Green);

	isGameOver = false;
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
}

void Game::handlePollEvents()
{
	while (window->pollEvent(*sfEvent))
	{
		if (sfEvent->type == sf::Event::Closed)
			window->close();
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
	window->draw(*circle);
}
