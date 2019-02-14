#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "GameWorld.h"
#include "MovingEntity.h"
enum PROJECTILE_TYPE { FRIENDLY_PROJECTILE, ENEMY_PROJECTILE };

class Projectile :
	public MovingEntity
{
private:

	bool hasBeenDestroyed = false;
	PROJECTILE_TYPE projectilType;
	int bounceCount = 0;
	void OnCollisionEnter(GameObject& otherGoRef);
	void OnCollisionStay(GameObject& otherGoRef);
	void StayInScreen();//override
	void Bounce();//
	void Destroy();//


public:
	Projectile(Vector2 _position, Vector2 _direction, PROJECTILE_TYPE _type);
	~Projectile();
	const PROJECTILE_TYPE GetProjectileType();
};

#endif // !PROJECTILE_H
