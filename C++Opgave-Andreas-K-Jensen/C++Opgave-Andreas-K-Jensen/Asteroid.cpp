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
Asteroid::Asteroid(Vector2 _direction, bool directionOverload) : Asteroid(Vector2::RandomOutOfScreenVector(), GenerateSize(), _direction)
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
	
	speed =   ASTEROID_SPEED_MODIFER /size; 

	entityType = ASTEROID;

	health = size / ASTEROID_HEALTH_MODIFER;
	if (health < 1)health = 1;



	sprite = SOIL_load_OGL_texture(ASTEROID_TEXTURE1, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

}


Asteroid::~Asteroid()
{
}

void Asteroid::Render()
{
	//TODO: Make it rotate depending on size (remember deltatime)

	GameObject::Render();
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
