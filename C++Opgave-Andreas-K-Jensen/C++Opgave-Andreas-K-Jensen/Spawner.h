#pragma once
#include "GameObject.h"
class Spawner
{
public:

	static GameObject SpawnGameObject(ENTITY_TYPE type);
	static GameObject SpawnRandomGameObject();

	Spawner();
	~Spawner();
};

