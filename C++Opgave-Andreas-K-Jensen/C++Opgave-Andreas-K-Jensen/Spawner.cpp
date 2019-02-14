#ifndef SPAWNER_H
#define SPAWNER_H

#include "Spawner.h"
#include "GameWorld.h"
#include "Asteroid.h"

GameObject* Spawner::SpawnGameObject(ENTITY_TYPE type)
{
	return	SpawnGameObject(type, true);
}

GameObject * Spawner::SpawnGameObject(ENTITY_TYPE type, bool collision)
{
	GameObject* go;


	switch (type)
	{
	case BLANK:
		DEBUG_LOG("error in Spawner:: SpawnGameobject!\n blank type");
		break;
	case ASTEROID:
		go = new Asteroid();
		break;
	case ENEMY:
		DEBUG_LOG("error in Spawner:: SpawnGameobject!\n enemy not yet implemented");

		break;
	case PLAYER:
		DEBUG_LOG("error in Spawner:: SpawnGameobject!\n player");

		break;
	case PROJECTILE:
		DEBUG_LOG("error in Spawner:: SpawnGameobject!\n projectile not yet implemented");

		break;
	default:
		DEBUG_LOG("error in Spawner:: SpawnGameobject!\n invalid type");
		break;
	}

	GameWorld::GetInstanceRef().gameObjectsToAdd.push(go);

	if (collision)
	{
		GameWorld::GetInstanceRef().collidersToAdd.push(new Collider(go));
	}


	return go;
}

Spawner::Spawner()
{
}


Spawner::~Spawner()
{
}
#endif // !SPAWNER_H
