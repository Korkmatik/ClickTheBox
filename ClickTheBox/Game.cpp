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
	isGameStart = false;

	initGame();

	startScreen = new StartScreen(window->getSize());
	gameOverScreen = new GameOverUI(window->getSize());
}

void Game::initGame()
{
	if (isGameInitialized)
		return;

	player = new Player(10);
	isGameOver = false;
	isGameStart = false;
	levelNumber = 1;
	maxEnemyCount = 10;
	spawnInterval = sf::milliseconds(1500);
	
	timeSinceLastSpawn = spawnInterval;
	timeToLevelUp = sf::seconds(2);
	
	backgroundClock.restart();
	deltaClock.restart();
	levelClock.restart();

	doLevelIncrease = true;

	enemyHandler = new EnemyHandler(window->getSize());

	hud = new Hud(
		window->getSize(),
		player->getScore(),
		player->getHealth(),
		levelNumber
	);

	levelClock.restart();

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
	delete gameOverScreen;
	delete startScreen;
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
	while (window->isOpen())
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
	handlePollEvents();

	if (!isGameOver && isGameStart) {
		updateMousePosition();
		updateGameObjects();
		spawnEnemyIfPossible();
		increaseLevelIfPossible();
		checkIfGameOver();
	}
}

void Game::spawnEnemyIfPossible()
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
		
		updatePlayerScore(points);

		if (!doLevelIncrease) {
			player->increaseHealth();
			updatePlayerHealth();
		}
		
		#ifdef _DEBUG
			std::cout << "Score: " << player->getScore() << "\n";
			std::cout << "Health: " << player->getHealth() << "\n" << std::endl;
		#endif // _DEBUG
	}
}

void Game::updatePlayerHealth()
{
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

sf::Color Game::getRandomBackGround()
{
	using namespace sf;

	static Color colors[] = {
				Color::Black,
				Color::White,
				Color::Red,
				Color::Green,
				Color::Blue,
				Color::Yellow,
				Color::Magenta,
				Color::Cyan
	};

	return colors[static_cast<int>(rand() % 8)];
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
		if (sfEvent->mouseButton.button == sf::Mouse::Left && !isGameOver && isGameStart) {
			handleMousePressedEvent();
		}
		if (sfEvent->mouseButton.button == sf::Mouse::Left && !isGameStart) {
			isGameStart = true;
		}
		if (sfEvent->mouseButton.button == sf::Mouse::Right && isGameOver) {
			restartGame();
		}
	}
}

void Game::updateGameObjects()
{
	int numberEnemiesOutOfScreen = enemyHandler->updateEnemies();
	player->decreaseHealth(numberEnemiesOutOfScreen);
	updatePlayerHealth();
}

void Game::spawnEnemy()
{
	if (enemyHandler->getNumberActiveEnemies() < maxEnemyCount) {
		enemyHandler->spawnEnemy(levelNumber);
	}
}

void Game::render()
{
	sf::Color backgroundColor;

	if (!doLevelIncrease &&
		!isGameOver) {

		static sf::Color randomBackground;
		if (static_cast<int>(backgroundClock.getElapsedTime().asMilliseconds()) > 300) {
			randomBackground = getRandomBackGround();
			backgroundClock.restart();
		}
		backgroundColor = randomBackground;
	}
	else {
		 backgroundColor = sf::Color::Black;
	}

	window->clear(backgroundColor);
	
	if (!isGameStart) {
		startScreen->render(window);
	}

	if (isGameOver) {
		gameOverScreen->setScore(player->getScore());
		gameOverScreen->render(window);
	}

	if (!isGameOver && isGameStart) {
		renderGameObjects();
		hud->render(window);
	}

	window->display();
}

void Game::renderGameObjects()
{
	enemyHandler->renderEnemies(window);
}
