#include "MovingEntity.h"
#include "Time.h"
#define DEFAULT_SPEED 1;

MovingEntity::MovingEntity() : GameObject(0,0,0)
{
	speed = DEFAULT_SPEED;
	direction = 0;
}

MovingEntity::MovingEntity(int x, int y, int z) :GameObject(x, y, z)
{
	speed = DEFAULT_SPEED;
	direction = 0;
}

MovingEntity::MovingEntity(int x, int y, int z, float _speed) :GameObject(x, y, z)
{
	speed = _speed;
	direction = 0;
}

MovingEntity::MovingEntity(float _speed) :MovingEntity()
{
	speed = _speed;
}



MovingEntity::~MovingEntity()
{
}

int MovingEntity::GetDirection()
{
	return direction;
}

void MovingEntity::Move()
{
	this->x += (direction * speed) * Time::GetDeltaTime(); //TODO: add deltatime

}

void MovingEntity::Update()
{
	Move();
}
