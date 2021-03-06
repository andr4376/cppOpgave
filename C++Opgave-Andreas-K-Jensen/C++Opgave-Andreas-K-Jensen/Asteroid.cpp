#include "Asteroid.h"
#include <chrono>

#define ASTEROID_TEXTURE1 "asteroid1.png"
#define ASTEROID_TEXTURE2 "asteroid2.png"
#define ASTEROID_TEXTURE3 "asteroid3.png"


Asteroid::Asteroid() : Asteroid(Vector2::RandomOutOfScreenPosition(), GenerateSize(), Vector2::RandomDirection())
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
	size = _size;	if (size < ASTEROID_MIN_SIZE) { size = ASTEROID_MIN_SIZE; }
	direction = _direction;

	speed = ASTEROID_SPEED_MODIFER / size;

	entityType = ASTEROID;

	health = size / (ASTEROID_HEALTH_MODIFER + 0.01); //0.01 to avoid 0 divide
	if (health < 1)health = 1;

	rotation = 0;

	sprite = SOIL_load_OGL_texture(ASTEROID_TEXTURE1, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

}


Asteroid::~Asteroid()
{
}



float Asteroid::GenerateSize()
{
	float size = rand() % (ASTEROID_MAX_SIZE + 1);

	return size > ASTEROID_MIN_SIZE ? size : ASTEROID_MIN_SIZE;

}

void Asteroid::Die()
{

	SplitIntoTwo();

	GameWorld::GetInstanceRef().DestroyGameObject(this);

	DEBUG_LOG("Asteroid is dead");

	KillAble::Die();
}

void Asteroid::SplitIntoTwo()
{
	if (size / 2 >= ASTEROID_MIN_SIZE)
	{
		for (float i = 0; i < 2; i++)
		{
			GameObject* go = new Asteroid(Vector2(position.x + (i / 100), position.y + (i / 100)), size / 2, direction);
			GameWorld::GetInstanceRef().gameObjectsToAdd.push(go);

			GameWorld::GetInstanceRef().collidersToAdd.push(new Collider(go));
		}
	}
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

void Asteroid::OnCollisionEnter(GameObject & otherGoRef)
{
	if (otherGoRef.GetEntityType() == PROJECTILE)
	{
		KillAble::TakeDamage();
	}

	MovingEntity::OnCollisionEnter(otherGoRef);
}


