#include "Player.h"
#include "GameWorld.h"
#include<iostream>

#define PLAYER_MOVEMENT_DAMPENING -2
#define PLAYER_TEXTURE "player.png"

#pragma region Constructors


Player::Player() : Player(VECTOR_ZERO, PLAYER_SPEED, PLAYER_SIZE)
{
}

Player::Player(Vector2 _pos, float _speed) : MovingEntity(_pos, _speed)
{
	sprite = SOIL_load_OGL_texture(PLAYER_TEXTURE, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

}
Player::Player(Vector2 _pos, float _speed, float _size) : MovingEntity(_pos, _speed, _size)
{
	sprite = SOIL_load_OGL_texture(PLAYER_TEXTURE, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

}
Player::Player(Vector2 _pos) : Player(_pos, PLAYER_SPEED, PLAYER_SIZE)
{

}
#pragma endregion

Player::~Player()
{
}

void Player::Update()
{

	DampenMovement(); //dampens movement. If no movementkeys are pressed, it will float

	HandleInput(); //Changes direction based on keypress


	DEBUG_LOG("x:" << position.x << "  y:" << position.y);
	DEBUG_LOG("dir x:" << direction.x << "  dir y:" << direction.y);

	//direction is normalized Move() , which is called in MovingEntity::Update() 
	MovingEntity::Update(); //Moves the player, based on its direction


}


//Slows down the player - for floating effect
void Player::DampenMovement()
{
	movementDampeningFactor = PLAYER_MOVEMENT_DAMPENING * Time::GetDeltaTime();
	direction += direction * movementDampeningFactor;
}

//Makes player stay inside the screen, if it tries to walk out of bounds
void Player::StayInScreen()
{
	if (position.x <= LEFT_GAME_BORDER && direction.x < 0 //if its at the leftmost border and it tries to walk left
		|| position.x >= RIGHT_GAME_BORDER && direction.x > 0)//if its at the rightmost border and it tries to walk right
	{
		direction.x = 0;//don't walk in that horizontal direction
	}
	if (position.y <= BOTTOM_GAME_BORDER && direction.y < 0 //if its at the bottom border and it tries to walk down
		|| position.y >= TOP_GAME_BORDER && direction.y > 0)//if its at the top border and it tries to walk up
	{
		direction.y = 0; //don't walk in that vertical direction
	}
}

void Player::HandleInput()
{
	movementInput = false;

	if (glfwGetKey(&GameWorld::GetWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		direction += VECTOR_LEFT;
		movementInput = true;
	}
	if (glfwGetKey(&GameWorld::GetWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		direction += VECTOR_RIGHT;
		movementInput = true;

	}
	if (glfwGetKey(&GameWorld::GetWindow(), GLFW_KEY_UP) == GLFW_PRESS)
	{
		direction += VECTOR_UP;
		movementInput = true;


	}
	if (glfwGetKey(&GameWorld::GetWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		direction += VECTOR_DOWN;
		movementInput = true;
	}

}

//Overrides Moving entities Move()
void Player::Move()
{
	if (movementInput) //if player has pressed a movement button
		direction.Normalize(); //Make sure the direction's magnitude remains 1 
	//if no movement input - don't normalize (creates floating effect)


	//Make sure player is inside screen
	StayInScreen();

	//Move the players position
	this->position += (direction * speed) * Time::GetDeltaTime();
}
