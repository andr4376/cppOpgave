#ifndef  KILLABLE_H
#define KILLABLE_H

#include"GameWorld.h"

class KillAble
{
protected:
	int health;
	virtual void Die();


public:

	~KillAble();
	int GetHealth();
	virtual void TakeDamage();


};

#endif // ! KILLABLE_H
