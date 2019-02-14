#include "Collider.h"
#include<iostream>



GameObject* Collider::GetGameObject()
{
	return gameObject;
}

Circle Collider::GetCollisionBox()
{
	return Circle(gameObject->GetPosition(), gameObject->GetSize() / 100);

}

void Collider::CheckCollision()
{
	//See if there are new collisions happening
	CheckCollisionEnter();

	//Check up on the previous collisions
	// are we still colliding, or did they exit the collision
	CheckCollisionStayAndEnter();

	//remove the ones that has exited collision
	RemoveIrrelevantColliders();
}





void Collider::RemoveIrrelevantColliders()
{

	//remove all colliders that are no loger relevant from this ones memory
	if (otherCollidersToRemove.size() > 0)
	{
		for (Collider* pCollToRemove : otherCollidersToRemove)
		{
			otherColliders.erase(std::remove(otherColliders.begin(), otherColliders.end(), pCollToRemove), otherColliders.end());
		}

		otherCollidersToRemove.clear();
	}
}

void Collider::CheckCollisionEnter()
{
	//for every collider in the game
	for (Collider* pOther : GameWorld::GetInstanceRef().GetColliders())
	{
		//if this one is not the current collider object
		if (pOther != this)
		{
			//If the two colliders' radius' overlaps
			if (GetCollisionBox().IntersectsWithOtherCircle(
				pOther->GetCollisionBox()))
			{
				//If vector does not Contain pOther:
				//Aka. If it does not currently know the other collider
				// using <Algorithm>
				if (std::find
				(otherColliders.begin(),//start of array
					otherColliders.end(), //end of array
					pOther) //element to find
					== otherColliders.end()) //if returned item is the end=> Vector does not contain item
				{
					//Theres a collision
					//oncollisionenter
					gameObject->OnCollisionEnter(*pOther->gameObject);
					DEBUG_LOG("oncoll enter");

					//Remember collider
					otherColliders.push_back(pOther);
				}

			}
		}
	}
}

void Collider::CheckCollisionStayAndEnter()
{
	//if we know other colliders
	if (otherColliders.size() > 0)
	{
		//for each of them
		for (Collider* otherCollPtr : otherColliders)
		{
			//if it's not this object
			if (otherCollPtr != this)//Should never happen, but just in case
			{
				//if we're still colliding 
				if (GetCollisionBox().IntersectsWithOtherCircle(otherCollPtr->GetCollisionBox()))
				{
					//CollisionStay
					gameObject->OnCollisionStay(*otherCollPtr->gameObject);

				}
				else //if we're no longer colliding
				{
					//CollisionExit
					gameObject->OnCollisionExit(*otherCollPtr->gameObject);

					//collider has left collision, so we remove it from this objects memory
					otherCollidersToRemove.push_back(otherCollPtr);
				}

			}


		}
	}
}

Collider::Collider(GameObject* _gameObject)
{
	gameObject = _gameObject;
}

Collider::~Collider()
{
}
