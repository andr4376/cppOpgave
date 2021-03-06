
#include "MovingEntity.h"
#include "Time.h"
#define DEFAULT_SPEED 1;

MovingEntity::MovingEntity() : MovingEntity(VECTOR_ZERO, DEFAULT_MOVING_ENTITY_SPEED, DEFAULT_OBJECT_SIZE)
{

}

MovingEntity::MovingEntity(Vector2 _pos) : MovingEntity(_pos, DEFAULT_MOVING_ENTITY_SPEED, DEFAULT_OBJECT_SIZE)
{
}

MovingEntity::MovingEntity(Vector2 _pos, float _speed) : MovingEntity(_pos, _speed, DEFAULT_OBJECT_SIZE)
{
}

//The constructor they all end up in
MovingEntity::MovingEntity(Vector2 _pos, float _speed, float _size) : GameObject(_pos, _size)
{
	speed = _speed;

	entityType = ASTEROID;

	rotation = 0;
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



void MovingEntity::StayInScreen()
{
	if (position.x - (size / 100) <= LEFT_GAME_BORDER && direction.x < 0 //if its at the leftmost border and it tries to walk left
		|| position.x + (size / 100) >= RIGHT_GAME_BORDER && direction.x > 0)//if its at the rightmost border and it tries to walk right
	{
		direction.x *= -1;//bounce horizontally

	}
	if (position.y - (size / 100) <= BOTTOM_GAME_BORDER && direction.y < 0 //if its at the bottom border and it tries to walk down
		|| position.y + (size / 100) >= TOP_GAME_BORDER && direction.y > 0)//if its at the top border and it tries to walk up
	{
		direction.y *= -1; //bounce vertically


	}
}

void MovingEntity::Move()
{

	StayInScreen();

	direction.Normalize();

	this->position += (direction * speed) * Time::GetDeltaTime();

}

void MovingEntity::OnCollisionStay(GameObject & goRef)
{
	//If this one is smaller that the other
	if (size <= goRef.GetSize())
	{					
		//this one should move away
			direction = position.DirectionAwayFromTarget(goRef.GetPosition());
		
			direction.Normalize();
	}

}

void MovingEntity::OnCollisionExit(GameObject & goRef)
{
}

void MovingEntity::Update()
{
	Move();
}

void MovingEntity::OnCollisionEnter(GameObject & goRef)
{

	GameObject::OnCollisionEnter(goRef);
}
