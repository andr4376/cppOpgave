#include "Vector2.h"



Vector2::Vector2() :Vector2(0, 0)
{
}


Vector2::Vector2(float _x, float _y)
{
	x = _x;
	y = _y;
}

Vector2 Vector2::operator+(Vector2 otherVector)
{
	return Vector2(x + otherVector.x, y + otherVector.y);
}

void Vector2::operator+=(Vector2 otherVector)
{
	x += otherVector.x;
	y += otherVector.y;
}

Vector2 Vector2::operator*(float multiplication)
{
	return Vector2(x*multiplication, y*multiplication);
}

void Vector2::operator*=(float multiplication)
{
	x *= multiplication;
	y *= multiplication;
}

float Vector2::Magnitude()
{
	return sqrt(x*x + y * y);
}

void Vector2::Normalize()
{
	if (x == 0 && y == 0)return;

	float magnitude = Magnitude();
	x /= magnitude;
	y /= magnitude;
}


//returns fDistance from this point to target
float Vector2::Distance(Vector2 othervector)
{
#pragma region Old Code
	//float a, b, c;

	//a = (x - othervector.x);

	//b = (y - othervector.y);

	//a *= a; //a^2
	//b *= b; //b^2

	//c = a + b; // c^2 = a^2 + b^2

	//return sqrtf(c); //square root to get result
#pragma endregion

	return Distance(*this, othervector);
}

//returns fDistance from a to b - Pythagoras Theorem 
float Vector2::Distance(Vector2 v1, Vector2 v2)
{
	float a, b, c;

	a = (v1.x - v2.x);

	b = (v1.y - v2.y);

	a *= a; //a^2
	b *= b; //b^2

	c = a + b; // c^2 = a^2 + b^2

	return sqrtf(c); //square root to get result
}

Vector2 Vector2::RandomOutOfScreenVector()
{
	return Vector2();//TODO: fix
}

Vector2 Vector2::RandomDirection()
{
	Vector2 direction;
	do
	{
		//TODO: make it not based on time?? can cause slow start
		//generate a number between -1 & +1
		srand(time(NULL));
		(direction.x = (rand() % (2 + 1))) - 1;

		srand(time(NULL));
		(direction.y = (rand() % (2 + 1))) - 1;

	} while (!(direction.x != 0 && direction.y != 0)); //while the direction != zero
	return direction;
}



Vector2::~Vector2()
{
}
