#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

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

	sf::CircleShape* circle;

	// Game logic attributes
	bool isGameOver;

	void update();
	void handlePollEvents();

	void render();
	void renderGameObjects();
};

