#include "Vector2.h"



Vector2::Vector2() :Vector2(0, 0)
{
}


Vector2::Vector2(int _x, int _y)
{
	x = _x;
	y = _y;
}

Vector2 Vector2::operator+(Vector2 otherVector)
{
	return Vector2(x + otherVector.x, y + otherVector.y);
}



Vector2::~Vector2()
{
}
