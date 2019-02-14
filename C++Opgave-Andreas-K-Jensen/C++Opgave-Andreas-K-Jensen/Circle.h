#ifndef CIRCLE_H
#define CIRCLE_H

#include"Vector2.h"
class Circle
{
private:
	Vector2 center;
	float radius;
public:
	Circle(Vector2 center, float radius);
	~Circle();

	bool ContainsPoint(Vector2 point);
	bool IntersectsWithOtherCircle(Circle other);

	Vector2 GetCenter();
	float GetRadius();
};

#endif // !CIRCLE_H
