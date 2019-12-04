#include "pch.h"

#include "EnemyHandler.hpp"

class EnemyHandlerTest : public ::testing::Test
{
public:
	EnemyHandler* enemyHandler;

	void SetUp() override
	{
		enemyHandler = new EnemyHandler(sf::Vector2u(200, 200));
	}

	void TearDown() override
	{
		delete enemyHandler;
	}

	void createEnemies(int number)
	{
		for (int i = 0; i < number; i++) {
			enemyHandler->spawnEnemy(500);
		}
	}
};

TEST_F(EnemyHandlerTest, InitTest)
{
	EXPECT_EQ(enemyHandler->getNumberActiveEnemies(), 0);
	EXPECT_EQ(enemyHandler->isAnyEnemyHit(sf::Vector2f(50.f, 50.f)), -1);
}

TEST_F(EnemyHandlerTest, SpawnTest)
{
	int numberSpawnedEnemies = 10;
	createEnemies(numberSpawnedEnemies);

	EXPECT_EQ(enemyHandler->getNumberActiveEnemies(), numberSpawnedEnemies);
}

TEST_F(EnemyHandlerTest, KillEnemiesTest)
{
	int numberEnemies = 10;
	createEnemies(numberEnemies);

	enemyHandler->killEnemy(0);
	enemyHandler->killEnemy(0);
	enemyHandler->killEnemy(0);
	numberEnemies -= 3;

	EXPECT_EQ(enemyHandler->getNumberActiveEnemies(), numberEnemies);
	
}