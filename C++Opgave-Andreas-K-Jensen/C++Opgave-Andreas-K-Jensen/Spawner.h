#pragma once
#include "GameObject.h"
class Spawner
{
public:

	static GameObject* SpawnGameObject(ENTITY_TYPE type);
	static GameObject* SpawnGameObject(ENTITY_TYPE type, bool collision);
	static GameObject* SpawnRandomGameObject();

	Spawner();
	~Spawner();
};

