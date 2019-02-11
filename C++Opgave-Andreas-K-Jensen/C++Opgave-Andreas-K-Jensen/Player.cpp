#include "Player.h"
#include "GameWorld.h"
#include<iostream>


void Player::Update()
{

	direction = VECTOR_ZERO; //0,0

	if (glfwGetKey(&GameWorld::GetWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		direction += VECTOR_LEFT;

	}
	if (glfwGetKey(&GameWorld::GetWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		direction += VECTOR_RIGHT;
	}
	if (glfwGetKey(&GameWorld::GetWindow(), GLFW_KEY_UP) == GLFW_PRESS)
	{
		direction += VECTOR_UP;

	}
	if (glfwGetKey(&GameWorld::GetWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		direction += VECTOR_DOWN;
	}


	//direction is normalized inMovingEntity::Move() , which is called in MovingEntity::Update() 

	MovingEntity::Update();
}

Player::Player() : MovingEntity()
{

}

Player::Player(Vector2 _pos, float _speed) : MovingEntity(_pos, _speed)
{
}
Player::Player(Vector2 _pos, float _speed, float _size) : MovingEntity(_pos, _speed, _size)
{
}
Player::Player(Vector2 _pos) : MovingEntity(_pos, PLAYER_SPEED)
{

}


Player::~Player()
{
}
