#ifndef MOVING_ENTITY_H
#define MOVING_ENTITY_H


#include "GameObject.h"
class MovingEntity :
	public GameObject
{
public:
	MovingEntity();
	MovingEntity(int x,int y, int z);
	MovingEntity(int x, int y, int z, float speed);
	MovingEntity(float speed);

	~MovingEntity();
	int GetDirection();
	void Update();

protected:
	int direction;

private:
	float speed;
	void Move();

};

#endif // !MOVING_ENTITY_H
