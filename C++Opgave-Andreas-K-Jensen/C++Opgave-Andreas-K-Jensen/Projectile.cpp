#include "Projectile.h"



void Projectile::OnCollisionEnter(GameObject & otherGoRef)
{
	if (!(projectilType == FRIENDLY_PROJECTILE && otherGoRef.GetEntityType() == PLAYER))
	{
		MovingEntity::OnCollisionStay(otherGoRef);
		Bounce();
	}
}

void Projectile::OnCollisionStay(GameObject & otherGoRef)
{
	if (!(projectilType == FRIENDLY_PROJECTILE && otherGoRef.GetEntityType() == PLAYER))
	{

		MovingEntity::OnCollisionStay(otherGoRef);

	}
}

void Projectile::StayInScreen()
{
	if (position.x - (size / 100) <= LEFT_GAME_BORDER && direction.x < 0 //if its at the leftmost border and it tries to walk left
		|| position.x + (size / 100) >= RIGHT_GAME_BORDER && direction.x > 0)//if its at the rightmost border and it tries to walk right
	{
		direction.x *= -1;//bounce horizontally
		Bounce();

	}
	if (position.y - (size / 100) <= BOTTOM_GAME_BORDER && direction.y < 0 //if its at the bottom border and it tries to walk down
		|| position.y + (size / 100) >= TOP_GAME_BORDER && direction.y > 0)//if its at the top border and it tries to walk up
	{

		direction.y *= -1;//bounce vertically

		Bounce();


	}
}

void Projectile::Bounce()
{
	if (!hasBeenDestroyed)
	{

		bounceCount++;

		if (bounceCount >= PROJECTILE_BOUNCE_THRESHOLD)
		{
			Destroy();
		}
	}
}

void Projectile::Destroy()
{
	hasBeenDestroyed = true;
	GameWorld::GetInstanceRef().DestroyGameObject(this);


}




Projectile::Projectile(Vector2 _position, Vector2 _direction, PROJECTILE_TYPE _type)
{
	position = _position;
	direction = _direction;
	size = PROJECTILE_SIZE;
	speed = PROJECTILE_SPEED;
	rotation = 0;
	entityType = PROJECTILE;
	projectilType = _type;
}

Projectile::~Projectile()
{
}

const PROJECTILE_TYPE Projectile::GetProjectileType()
{
	return projectilType;
}
