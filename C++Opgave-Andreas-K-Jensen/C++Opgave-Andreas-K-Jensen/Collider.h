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

	void RemoveIrrelevantColliders();
	void CheckCollisionEnter();
	void CheckCollisionStayAndEnter();

public:
	Collider(GameObject* _gameObject);
	~Collider();

	std::vector<Collider*> otherColliders;
	std::vector<Collider*> otherCollidersToRemove;
	GameObject* GetGameObject();
	Circle GetCollisionBox();
	void CheckCollision();
};

#endif // !COLLIDER_H
