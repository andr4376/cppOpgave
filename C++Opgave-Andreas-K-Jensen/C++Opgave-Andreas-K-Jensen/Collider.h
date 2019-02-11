#ifndef COLLIDER_H
#define COLLIDER_H
#include"GameObject.h"
#include "Circle.h"
#include"GameWorld.h"
#include <vector>
#include <algorithm>

class Collider
{

private:
	GameObject* gameObject;
	std::vector<Collider*> otherColliders;
	std::vector<Collider*> otherCollidersToRemove;
public:
	Collider(GameObject* _gameObject);
	~Collider();

	Circle GetCollisionBox();
	void CheckCollision();
};

#endif // !COLLIDER_H
