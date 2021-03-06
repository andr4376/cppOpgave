#include "Player.h"
#include "GameWorld.h"
#include<iostream>
#define PLAYER_TEXTURE "player.png"
#define PLAYER_HEALTHBAR_TEXTURE "healthBar.png"

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

	healthBarSprite = SOIL_load_OGL_texture(PLAYER_HEALTHBAR_TEXTURE, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	glBindTexture(GL_TEXTURE_2D, healthBarSprite); //load healthbarsprite to gpu

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
	if (invincible)
	{
		//checks if player should remain invincible
		//(player becomes invincible for a duration after getting hit)
		CanTakeDamage();
	}

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
	MovementInputHandler();
	ShootInputHandler();
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
	GameWorld::GetInstanceRef().DestroyGameObject(this);
}

void Player::Render()
{
	//Draw Player Cyan
	if (invincible) { glColor3f(0, 1, 1); }

	MovingEntity::Render();
	DrawHealth();
}

void Player::DrawHealth()
{
	float healthBarWidht = 0.33 * health; //widht of the healbar

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, healthBarSprite);

	//red
	glColor3f(1, 0, 0);

	//Draw healthbar Cyan
	if (invincible) { glColor3f(0, 1, 1); }

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.95, -0.95, 0); //bottom left
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.2 + healthBarWidht, -0.95, 0); //bottom right
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.2 + healthBarWidht, -0.9, 0); //top right
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.95, -0.9, 0); //top left
	glEnd();

	//make green and blue % of what health is remaining
	//The less health, the more red
	glColor3f(1, GetBlueAndGreenColorIntensity(), GetBlueAndGreenColorIntensity());


	glPopMatrix();
}

float Player::GetBlueAndGreenColorIntensity()
{
	float intensity = (float)health / PLAYER_BASE_HEALTH;
	return intensity;
}

bool Player::CanTakeDamage()
{
	if (invincible) // if player is currently invincible
	{
		//get elapsed time since hit
		fSecond elapsedTime = Clock::now() - takeDamageTimeStamp;

		//if it exceeds the cooldown
		if (elapsedTime.count() >= PLAYER_INVINCIBILITY_TIME_SECONDS)
		{
			//player can get hit
			invincible = false;
			return true;
		}
		//else he cannot
		return false;
	}

	//if not invincible
	return true;
}

bool Player::CanShoot()
{
	//get elapsed time since last shot
	fSecond elapsedTime = Clock::now() - shootTimeStamp;

	//if it exceeds the cooldown
	if (elapsedTime.count() >= PLAYER_SHOOT_COOLDOWN)
	{
		//player can shoot 		
		return true;
	}
	//else he cannot
	return false;

}

void Player::TakeDamage()
{

	if (CanTakeDamage())
	{
		KillAble::TakeDamage();

		takeDamageTimeStamp = Clock::now();

		invincible = true;
	}

}

void Player::MovementInputHandler()
{
	movementInput = false;

	// A
	if (glfwGetKey(&GameWorld::GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		direction += VECTOR_LEFT;
		movementInput = true;
	}
	//D
	if (glfwGetKey(&GameWorld::GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		direction += VECTOR_RIGHT;
		movementInput = true;

	}
	//W
	if (glfwGetKey(&GameWorld::GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{
		direction += VECTOR_UP;
		movementInput = true;


	}
	//S
	if (glfwGetKey(&GameWorld::GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
	{
		direction += VECTOR_DOWN;
		movementInput = true;
	}
}

void Player::ShootInputHandler()
{
	if (CanShoot())
	{

		bool shootInput = false;

		Vector2 shootDirection = VECTOR_ZERO;
		//LEFT
		if (glfwGetKey(&GameWorld::GetWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			shootDirection += VECTOR_LEFT;
			shootInput = true;
		}
		//RIGHT 
		else if (glfwGetKey(&GameWorld::GetWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			shootDirection += VECTOR_RIGHT;
			shootInput = true;

		}
		//UP 
		if (glfwGetKey(&GameWorld::GetWindow(), GLFW_KEY_UP) == GLFW_PRESS)
		{
			shootDirection += VECTOR_UP;
			shootInput = true;


		}
		//DOWN
		else if (glfwGetKey(&GameWorld::GetWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			shootDirection += VECTOR_DOWN;
			shootInput = true;
		}

		if (shootInput)
		{
			shootDirection.Normalize();
			Shoot(shootDirection);
		}
	}
}

void Player::Shoot(Vector2 _direction)
{
	Projectile* pProjectile = new Projectile(position, _direction, FRIENDLY_PROJECTILE);

	GameWorld::GetInstanceRef().gameObjectsToAdd.push(pProjectile);
	GameWorld::GetInstanceRef().collidersToAdd.push(new Collider(pProjectile));

	shootTimeStamp = Clock::now();
}
