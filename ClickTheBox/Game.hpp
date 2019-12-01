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

	void update();
	void handlePollEvents();
	void updateGameObjects();

	void render();
	void renderGameObjects();
};

