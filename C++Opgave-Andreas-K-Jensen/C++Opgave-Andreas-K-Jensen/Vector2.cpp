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

void Vector2::Normalize()
{	

	float m = sqrt(x*x + y*y);	
	x /= m;
	y /= m;

	

}

float Vector2::Magnitude()
{
	return sqrt(x*x + y * y);
}



Vector2::~Vector2()
{
}
