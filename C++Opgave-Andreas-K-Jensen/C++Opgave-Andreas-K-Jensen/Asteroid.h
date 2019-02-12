#pragma once
#include "MovingEntity.h"
#include "Vector2.h"
#include "KillAble.h"
class Asteroid :
	public MovingEntity,
	public KillAble
{
public:
	Asteroid();
	Asteroid(Vector2 _position);
	Asteroid(Vector2 _position, float _size);
	Asteroid(Vector2 _position, float _size, Vector2 _direction);

	~Asteroid();

private:
	float GenerateSize();
	void Die();

};

