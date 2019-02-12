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
		if (pOther != this)
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
					DEBUG_LOG("CollisionEnter");
					otherColliders.push_back(pOther);

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
