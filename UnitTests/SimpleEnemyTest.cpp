#include "pch.h"

#include "SimpleEnemy.hpp"
#include "SFML/Graphics.hpp"

class SimpleEnemyTest : public ::testing::Test
{
public:
	SimpleEnemy* enemy;
	sf::Vector2u* screenDimensions;

	void SetUp() override 
	{
		screenDimensions = new sf::Vector2u(500, 600);
		enemy = new SimpleEnemy(*screenDimensions);
	}

	void TearDown() override
	{
		delete screenDimensions;
		delete enemy;
	}
};