#ifndef ASTEROID_H
#define ASTEROID_H


#include "MovingEntity.h"
#include "Vector2.h"
#include "KillAble.h"
#include "Time.h"
class Asteroid :
	public MovingEntity,
	public KillAble
{
public:
	Asteroid();
	Asteroid(Vector2 _position);
	Asteroid(Vector2 _position, float _size);
	Asteroid(Vector2 _position, float _size, Vector2 _direction);

	~Asteroid();

	static float GenerateSize();
private:
	void Die();
	void SplitIntoTwo();
	void Move();
	void OnCollisionEnter(GameObject& goRef);//
};


#endif // !ASTEROID_H
