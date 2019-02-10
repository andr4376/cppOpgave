#pragma once
#include "MovingEntity.h"
class Player :
	public MovingEntity
{
public:

	void Update();
	Player();
	~Player();
};

