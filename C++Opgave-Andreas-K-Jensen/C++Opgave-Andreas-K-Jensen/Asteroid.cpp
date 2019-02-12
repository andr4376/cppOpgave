#include "Asteroid.h"
#include <chrono>

#define ASTEROID_TEXTURE1 "asteroid1.png"
#define ASTEROID_TEXTURE2 "asteroid2.png"
#define ASTEROID_TEXTURE3 "asteroid3.png"


Asteroid::Asteroid() : Asteroid(Vector2::RandomOutOfScreenVector(), GenerateSize(), Vector2::RandomDirection())
{

}

Asteroid::Asteroid(Vector2 _position) : Asteroid(_position, GenerateSize(), Vector2::RandomDirection())
{

}

Asteroid::Asteroid(Vector2 _position, float _size) : Asteroid(_position, _size, Vector2::RandomDirection())
{
}

Asteroid::Asteroid(Vector2 _position, float _size, Vector2 _direction)
{
	position = _position;
	size = _size;
	direction = _direction;

	speed = ASTEROID_SPEED_MODIFER / size;

	entityType = ASTEROID;

	health = size / ASTEROID_HEALTH_MODIFER;
	if (health < 1)health = 1;

	rotation = 0;

	sprite = SOIL_load_OGL_texture(ASTEROID_TEXTURE1, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

}


Asteroid::~Asteroid()
{
}



float Asteroid::GenerateSize()
{

	srand(time(NULL));

	float size = rand() % (ASTEROID_MAX_SIZE + 1);

	return size > ASTEROID_MIN_SIZE ? size : ASTEROID_MIN_SIZE;

}

void Asteroid::Die()
{

	KillAble::Die();
}

void Asteroid::Move()
{
	//which direction is it moving towards the most?
	float strongestDirection = fabs(direction.x) > fabs(direction.y) ? direction.x : direction.y;

	//use that to define it's rotation pattern
	float newRot = rotation + strongestDirection * (ASTEROID_ROTATION_SPEED*speed) * Time::GetDeltaTime();

	//change actual rotation
	SetRotation(newRot);

	//base move
	MovingEntity::Move();
}

