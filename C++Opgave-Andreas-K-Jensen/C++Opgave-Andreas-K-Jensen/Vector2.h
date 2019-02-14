#ifndef VECTOR_2
#define VECTOR_2
#include <math.h>
#include <stdlib.h>
#include <chrono>

//Predetermined directions
#define VECTOR_ZERO Vector2(0,0)
#define VECTOR_UP Vector2(0,1)
#define VECTOR_DOWN Vector2(0,-1)
#define VECTOR_LEFT Vector2(-1,0)
#define VECTOR_RIGHT Vector2(1,0)


//A struct containing an x and a y coordinate/point
//Also contains vector math
struct Vector2
{
	float x;
	float y;

	Vector2();
	Vector2(float _x, float _y);
	~Vector2();

	//Allows adding vectors together 
	Vector2 operator + (Vector2 otherVector); //operator overload
	Vector2 operator - (Vector2 otherVector); //operator overload

	void operator += (Vector2 otherVector); //adds another vector on this vector
	Vector2 operator * (float multiplication);
	void operator *= (float multiplication);
	bool operator == (Vector2 other);


	void Normalize();
	float Magnitude();
	float Distance(Vector2 othervector);
	static float Distance(Vector2 a, Vector2 b);
	Vector2 DirectionTowardsTarget(Vector2 other);
	Vector2 DirectionAwayFromTarget(Vector2 other);
	static Vector2 RandomOutOfScreenPosition();
	static Vector2 RandomDirection();

};

#endif // !VECTOR_2
