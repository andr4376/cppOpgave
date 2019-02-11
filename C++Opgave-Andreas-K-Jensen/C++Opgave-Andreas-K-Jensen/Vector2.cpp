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



float Vector2::Distance(Vector2 othervector) 
{
	float a, b, c;

	a = (x - othervector.x);

	b = (y - othervector.y);

	a *= a; //a^2
	b *= b; //b^2

	c = a + b; // c^2 = a^2 + b^2

	return sqrtf(c); //square root to get result
}

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



Vector2::~Vector2()
{
}
