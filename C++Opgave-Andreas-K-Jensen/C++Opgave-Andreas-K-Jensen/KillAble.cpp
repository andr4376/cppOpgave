#include "KillAble.h"





KillAble::~KillAble()
{
}

void KillAble::TakeDamage()
{
	health--;

	if (health <= 0)
	{
		health = 0;
		Die();
	}
}

void KillAble::Die()
{
	//TODO: remove game obejct and all pointers!!

	//GameWorld::GetInstanceRef().gameObjectsToRemove.push_back(this);

}

int KillAble::GetHealth()
{
	return health;
}

