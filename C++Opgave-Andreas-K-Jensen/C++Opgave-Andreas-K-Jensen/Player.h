#ifndef PLAYER_H
#define PLAYER_H

#include "MovingEntity.h"
#include "Time.h"
#include "KillAble.h"
#include "Projectile.h"

//The player controlled objects - Inherites from MovingEntity AND Killable


class Player :
	public MovingEntity,
	public KillAble
{

private:
	bool movementInput; //If no input, allows player to float
	float movementDampeningFactor; //floating intensity when no input
	GLuint healthBarSprite = NULL; //texture of game object
	TimePoint takeDamageTimeStamp = Clock::now();
	bool invincible = false;

	TimePoint shootTimeStamp = Clock::now();
public:

	void Update();
	Player();
	Player(Vector2 _pos);
	Player(Vector2 _pos, float speed);
	Player(Vector2 _pos, float speed, float _size);

	~Player();

	void OnCollisionEnter(GameObject& goRef);//

private:
	void DampenMovement(); //slows player down to make floating effect
	void HandleInput(); //Handles input
	void Move(); //Overrides MovingEntity's move - this one adds the floating effect
	void Die();
	void Render(); // overrides MovingEntities draw
	void DrawHealth();
	float GetBlueAndGreenColorIntensity(); //for visual effect when low health
	bool CanTakeDamage();
	bool CanShoot();
	void TakeDamage();
	void MovementInputHandler();
	void ShootInputHandler();
	void Shoot(Vector2 _direction);

protected:
	void StayInScreen(); //makes sure player remains on screen when he attempts to move
};

#endif // !PLAYER_H
