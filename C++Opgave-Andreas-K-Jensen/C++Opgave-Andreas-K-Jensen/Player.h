#ifndef PLAYER_H
#define PLAYER_H

#include "MovingEntity.h"
class Player :
	public MovingEntity
{
public:

	void Update();
	Player();
	Player(int x, int y, int z, float speed);
	Player(int x, int y, int z);


	~Player();
};

#endif // !PLAYER_H
