#include "Circle.h"






Circle::Circle(Vector2 _center, float _radius)
{
	center = _center;
	radius = _radius;
}

Circle::Circle()
{
}

Circle::~Circle()
{
}

//If the distance from this to the other is less or equal to radius, it contains the point.
bool Circle::ContainsPoint(Vector2 point)
{
	float distance = center.Distance(point);

	return distance <= radius ? true : false;


}

//determines if this circle is inside another circle
bool Circle::IntersectsWithOtherCircle(Circle other)
{

	float distance = center.Distance(other.center);

	return distance <= radius + other.radius ? true : false;
}

Vector2 Circle::GetCenter()
{
	return center;
}

float Circle::GetRadius()
{
	return radius;
}
