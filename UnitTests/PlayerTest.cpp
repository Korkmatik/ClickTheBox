#include "pch.h"

#include "Player.hpp"

class PlayerTest : public ::testing::Test 
{
public:
	Player* player;

	int startingHealth;

	void SetUp() override 
	{
		startingHealth = 10;

		player = new Player(startingHealth);
	}

	void TearDown() override
	{
		delete player;
	}
};

TEST_F(PlayerTest, initTest)
{
	ASSERT_FALSE(player->isDead());
	ASSERT_EQ(player->getScore(), 0);
	ASSERT_EQ(player->getHealth(), startingHealth);
}

TEST_F(PlayerTest, healthTest)
{
	int minusHealth = 5;
	int expectedHealth = startingHealth - minusHealth;

	player->decreaseHealth(minusHealth);
	ASSERT_EQ(player->getHealth(), expectedHealth);

	player->increaseHealth();
	expectedHealth += 1;

	ASSERT_EQ(player->getHealth(), expectedHealth);

	player->increaseHealth();
	expectedHealth += 1;

	ASSERT_EQ(player->getHealth(), expectedHealth);

	expectedHealth -= minusHealth;
	player->decreaseHealth(minusHealth);
	ASSERT_EQ(player->getHealth(), expectedHealth);
}

TEST_F(PlayerTest, scoreTest)
{
	int expectedScore = player->getScore() + 10;
	player->addToScore(10);
	EXPECT_EQ(expectedScore, player->getScore());

	expectedScore += 20;
	player->addToScore(20);
	EXPECT_EQ(expectedScore, player->getScore());

	player->addToScore(-10);
	EXPECT_EQ(expectedScore, player->getScore());
}

TEST_F(PlayerTest, isDeadTest) 
{
	ASSERT_EQ(player->getHealth(), startingHealth);

	player->decreaseHealth(startingHealth-5);
	EXPECT_FALSE(player->isDead());

	player->decreaseHealth(startingHealth);
	EXPECT_TRUE(player->isDead());

	for (int i = 0; i < startingHealth + 50; i++) {
		player->increaseHealth();
	}
	EXPECT_FALSE(player->isDead());
}