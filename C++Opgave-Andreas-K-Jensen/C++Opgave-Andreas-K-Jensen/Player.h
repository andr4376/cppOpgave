#ifndef PLAYER_H
#define PLAYER_H

#include "MovingEntity.h"
#include "Time.h"

class Player :
	public MovingEntity
{

private:
	bool movementInput; //If no input, allows player to float
	float movementDampeningFactor; //floating intensity when no input
public:

	void Update();
	Player();
	Player(Vector2 _pos, float speed);
	Player(Vector2 _pos, float speed, float _size);

	Player(Vector2 _pos);


	~Player();

private:
	void DampenMovement();
	void StayInScreen();
	void HandleInput();
	void Move();
};

#endif // !PLAYER_H
