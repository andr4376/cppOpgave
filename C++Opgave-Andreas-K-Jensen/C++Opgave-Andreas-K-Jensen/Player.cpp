#include "Player.h"
#include "GameWorld.h"
#include<iostream>

#define PLAYER_MOVEMENT_DAMPENING -2
#define PLAYER_TEXTURE "player.png"

#pragma region Constructors


Player::Player() : Player(VECTOR_ZERO, PLAYER_SPEED, PLAYER_SIZE)
{
}
Player::Player(Vector2 _pos) : Player(_pos, PLAYER_SPEED, PLAYER_SIZE)
{
}

Player::Player(Vector2 _pos, float _speed) : Player(_pos, _speed, PLAYER_SIZE)
{
}

//The constructor where they all end up
Player::Player(Vector2 _pos, float _speed, float _size) : MovingEntity(_pos, _speed, _size)
{
	sprite = SOIL_load_OGL_texture(PLAYER_TEXTURE, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	entityType = PLAYER;

	health = PLAYER_BASE_HEALTH;

}
#pragma endregion

Player::~Player()
{
}

void Player::OnCollisionEnter(GameObject & goRef)
{
	DEBUG_LOG("player coll enter");

	if (goRef.GetEntityType() == ENEMY || goRef.GetEntityType() == ASTEROID)
	{
		TakeDamage();
	}


	MovingEntity::OnCollisionEnter(goRef);
}

void Player::Update()
{

	DampenMovement(); //dampens movement. If no movementkeys are pressed, it will float

	HandleInput(); //Changes direction based on keypress



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
	if (position.x - (size / 100) <= LEFT_GAME_BORDER && direction.x < 0 //if its at the leftmost border and it tries to walk left
		|| position.x + (size / 100) >= RIGHT_GAME_BORDER && direction.x > 0)//if its at the rightmost border and it tries to walk right
	{
		direction.x *= -1;//bounce horizontally

		if (movementInput)direction.x = 0;//don't walk in that horizontal direction
	}
	if (position.y - (size / 100) <= BOTTOM_GAME_BORDER && direction.y < 0 //if its at the bottom border and it tries to walk down
		|| position.y + (size / 100) >= TOP_GAME_BORDER && direction.y > 0)//if its at the top border and it tries to walk up
	{
		direction.y *= -1; //bounce vertically

		if (movementInput)direction.y = 0;//don't walk in that vertical direction

	}
}

void Player::HandleInput()
{
	movementInput = false;

	//LEFT / A
	if (glfwGetKey(&GameWorld::GetWindow(), GLFW_KEY_LEFT) == GLFW_PRESS
		|| glfwGetKey(&GameWorld::GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		direction += VECTOR_LEFT;
		movementInput = true;
	}
	//RIGHT /D
	if (glfwGetKey(&GameWorld::GetWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS
		|| glfwGetKey(&GameWorld::GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		direction += VECTOR_RIGHT;
		movementInput = true;

	}
	//UP / W
	if (glfwGetKey(&GameWorld::GetWindow(), GLFW_KEY_UP) == GLFW_PRESS
		|| glfwGetKey(&GameWorld::GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{
		direction += VECTOR_UP;
		movementInput = true;


	}
	//DOWN/S
	if (glfwGetKey(&GameWorld::GetWindow(), GLFW_KEY_DOWN) == GLFW_PRESS
		|| glfwGetKey(&GameWorld::GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
	{
		direction += VECTOR_DOWN;
		movementInput = true;
	}

}

//Overrides Moving entities Move() -> doesn't call MovingEntity::Move() because player needs to control whether or not its direction is normalized
void Player::Move()
{
	if (movementInput || direction.Magnitude() > 1) //if player has pressed a movement button, or the direction magnitude >1
		direction.Normalize(); //Make sure the direction's magnitude remains 1 - to stop player from moving faster
	//if no movement input - don't normalize (creates floating effect)


	//Make sure player is inside screen
	StayInScreen();

	//Move the players position
	this->position += (direction * speed) * Time::GetDeltaTime();
}

void Player::Die()
{


	GameWorld::GetInstanceRef().gameObjectsToRemove.push_back(this);

	Collider* myColPtr = nullptr;

	for (Collider* colPtr : GameWorld::GetInstanceRef().colliders)
	{
		if (colPtr->GetGameObject() == this)
		{
			colPtr = myColPtr;
			break;
		}
	}

	GameWorld::GetInstanceRef().collidersToRemove.push_back(myColPtr);

	DEBUG_LOG("Player is dead");
}

void Player::Render()
{
	MovingEntity::Render();
	DrawHealth();
}

void Player::DrawHealth()
{
	//TODO: visualize playe rhealth
	float widht = 0.33 * health;

	glPushMatrix(); //Lægger en matrise på stakken, således kun denne manipuleres
	glBindTexture(GL_TEXTURE_2D, sprite); //Binder teksturen (Anvender til ved rendering af vertices)
	glBegin(GL_QUADS);
	// Front Face


	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.95, -0.95, 0); //bottom left
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1 + widht, -0.95, 0); //bottom right
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1 + widht, -0.9, 0); //top right
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.95, -0.9, 0); //top left
	glEnd();
	glPopMatrix(); // Fjerner matrisen på stakken (dvs. nulstiller til udgangspunkt)
}
