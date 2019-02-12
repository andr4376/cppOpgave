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
}

int KillAble::GetHealth()
{
	return health;
}

