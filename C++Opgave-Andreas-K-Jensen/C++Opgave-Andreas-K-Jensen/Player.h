#ifndef PLAYER_H
#define PLAYER_H

#include "MovingEntity.h"
class Player :
	public MovingEntity
{
public:

	void Update();
	Player();
	Player(Vector2 _pos, float speed);
	Player(Vector2 _pos, float speed,float _size);

	Player(Vector2 _pos);


	~Player();
};

#endif // !PLAYER_H
