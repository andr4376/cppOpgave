
#include "MovingEntity.h"
#include "Time.h"
#define DEFAULT_SPEED 1;

MovingEntity::MovingEntity() : GameObject(Vector2())
{
	speed = DEFAULT_SPEED;
	direction = Vector2();
}

MovingEntity::MovingEntity(Vector2 _pos) :GameObject(_pos)
{
	speed = DEFAULT_SPEED;
	direction = Vector2();
}

MovingEntity::MovingEntity(Vector2 _pos, float _speed) :GameObject(_pos)
{
	speed = _speed;
	direction = Vector2();
}
MovingEntity::MovingEntity(Vector2 _pos, float _speed, float _size) : GameObject(_pos, _size)
{
	speed = _speed;
}

MovingEntity::MovingEntity(float _speed) : MovingEntity()
{
	speed = _speed;
}



MovingEntity::~MovingEntity()
{
}

Vector2  MovingEntity::GetDirection()
{
	return direction;
}

void MovingEntity::Move()
{
	direction.Normalize();

	this->position += (direction * speed) * Time::GetDeltaTime();

}

void MovingEntity::Update()
{
	Move();
}
