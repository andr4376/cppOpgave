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

Vector2 Vector2::operator-(Vector2 otherVector)
{
	return Vector2();
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

bool Vector2::operator==(Vector2 other) { return (this->x == other.x && this->y == other.y); }

float Vector2::Magnitude() { return sqrt(x*x + y * y); }

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

Vector2 Vector2::DirectionTowardsTarget(Vector2 other) { return Vector2(other.x - this->x, other.y - this->y); }

Vector2 Vector2::DirectionAwayFromTarget(Vector2 other) { return Vector2(this->x - other.x, this->y - other.y); }

Vector2 Vector2::RandomOutOfScreenPosition()
{
	Vector2 position;
	do
	{
		//TODO: j
		//generate a number between -1 & +1
		position.x = (float)(((rand() % (600 + 1))) - 300) / 100;

		position.y = (float)(((rand() % (600 + 1))) - 300) / 100;

	} while (!((position.x <-1.5 || position.x > 1.5) &&
		(position.y <-1.5 || position.y > 1.5))); //untill its guarenteed to be outside of the screen
	return position;
}

Vector2 Vector2::RandomDirection()
{
	Vector2 direction;
	do
	{
		//TODO: j
		//generate a number between -1 & +1
		direction.x = (float)(((rand() % (200 + 1))) - 100) / 100;

		direction.y = (float)(((rand() % (200 + 1))) - 100) / 100;

	} while (!(direction.x != 0 && direction.y != 0)); //while the direction != zero
	return direction;
}



Vector2::~Vector2()
{
}
