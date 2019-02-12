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
	for (Collider* pOther : GameWorld::GetInstanceRef().GetColliders())
	{


		Circle c = GetCollisionBox();
		if (GetCollisionBox().IntersectsWithOtherCircle(pOther->GetCollisionBox()))
		{
			//If vector does not Contain pOther:
			// using <Algorithm>
			if (std::find
			(otherColliders.begin(),//start of array
				otherColliders.end(), //end of array
				pOther) //element to find
				== otherColliders.end()) //if returned item is the last item => Vector does not contain item
			{
				//oncollisionenter
				gameObject->OnCollisionEnter(*pOther->gameObject);
				DEBUG_LOG("oncoll enter");

				otherColliders.push_back(pOther);

			}

		}
	}



	if (otherColliders.size() > 0)
	{

		for (Collider* otherCollPtr : otherColliders)
		{


			if (otherCollPtr != this)
			{
				if (GetCollisionBox().IntersectsWithOtherCircle(otherCollPtr->GetCollisionBox()))
				{
					gameObject->OnCollisionStay(*otherCollPtr->gameObject);
					DEBUG_LOG("oncoll stay");

				}
				else
				{
					gameObject->OnCollisionExit(*otherCollPtr->gameObject);
					DEBUG_LOG("Oncoll exit");

					otherCollidersToRemove.push_back(otherCollPtr);
				}

			}


		}
	}

	RemoveKnownColliders();
}





void Collider::RemoveKnownColliders()
{

	//remove all colliders from this ones memrory
	if (otherCollidersToRemove.size() > 0)
	{
		for (Collider* pCollToRemove : otherCollidersToRemove)
		{
			otherColliders.erase(std::remove(otherColliders.begin(), otherColliders.end(), pCollToRemove), otherColliders.end());
		}

		otherCollidersToRemove.clear();
	}
}

Collider::Collider(GameObject* _gameObject)
{
	gameObject = _gameObject;
}

Collider::~Collider()
{
}
