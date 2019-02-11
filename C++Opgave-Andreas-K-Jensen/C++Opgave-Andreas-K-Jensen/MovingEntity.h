#ifndef MOVING_ENTITY_H
#define MOVING_ENTITY_H


#include "GameObject.h"
class MovingEntity :
	public GameObject
{
public:
	MovingEntity();
	MovingEntity(Vector2 _pos);
	MovingEntity(Vector2 _pos, float speed);
	MovingEntity(Vector2 _pos, float speed, float _size);
	MovingEntity(float speed);

	~MovingEntity();
	Vector2  GetDirection();
	void Update();

protected:
	Vector2 direction;
	float speed;

	virtual void Move();
private:

};

#endif // !MOVING_ENTITY_H
