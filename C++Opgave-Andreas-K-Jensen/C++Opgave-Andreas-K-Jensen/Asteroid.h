#ifndef ASTEROID_H
#define ASTEROID_H


#include "MovingEntity.h"
#include "Vector2.h"
#include "KillAble.h"
class Asteroid :
	public MovingEntity,
	public KillAble
{
public:
	Asteroid();
	Asteroid(Vector2 _position);
	Asteroid(Vector2 _direction,bool directionOverload);
	Asteroid(Vector2 _position, float _size);
	Asteroid(Vector2 _position, float _size, Vector2 _direction);

	~Asteroid();
	void Render(); //override from game object

	static float GenerateSize();
private:
	void Die();


};


#endif // !ASTEROID_H
