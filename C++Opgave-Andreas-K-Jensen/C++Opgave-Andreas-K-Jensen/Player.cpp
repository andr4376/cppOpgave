#include "Player.h"
#include "GameWorld.h"
#include<iostream>

#define PLAYER_SPEED = 10;

void Player::Update()
{

	direction = 0;
	if (glfwGetKey(&GameWorld::GetWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		direction = -1; // Gå til venstre
	}
	if (glfwGetKey(&GameWorld::GetWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		direction = 1; // Gå til højre
	}

	MovingEntity::Update();
}

Player::Player()
{
	
}


Player::~Player()
{
}
