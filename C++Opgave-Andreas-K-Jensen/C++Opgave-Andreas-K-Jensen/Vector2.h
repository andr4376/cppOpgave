#ifndef VECTOR_2
#define VECTOR_2
#include <math.h>
struct Vector2
{
	float x;
	float y;

	Vector2();
	Vector2(float _x, float _y);
	~Vector2();

	//Allows adding vectors together 
	Vector2 operator + (Vector2 otherVector); //operator overload
	void Normalize();
	float Magnitude();

};

#endif // !VECTOR_2
