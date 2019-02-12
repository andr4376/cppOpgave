#include "Asteroid.h"



Asteroid::Asteroid() : Asteroid(Vector2::RandomOutOfScreenVector(), GenerateSize(), Vector2::RandomDirection())
{
}

Asteroid::Asteroid(Vector2 _direction) : Asteroid(Vector2::RandomOutOfScreenVector(), GenerateSize(), _direction)
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
}


Asteroid::~Asteroid()
{
}

float Asteroid::GenerateSize()
{
	float size = rand() % ASTEROID_MAX_SIZE + 1;

	return size > ASTEROID_MIN_SIZE ? size : ASTEROID_MIN_SIZE;

}

void Asteroid::Die()
{
	KillAble::Die();
}
