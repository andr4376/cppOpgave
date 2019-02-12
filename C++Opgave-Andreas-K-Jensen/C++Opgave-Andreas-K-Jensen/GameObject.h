#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Globals.h"
#include <SOIL.h>
#include <GLFW\glfw3.h>
#include "Vector2.h"
#include<iostream>

//The different entity types the game has
enum ENTITY_TYPE { BLANK, OBSTACLE, ENEMY, PLAYER, PROJECTILE};

class GameObject
{

protected:
	Vector2 position; //it's position in a 2d space
	float size = 1;
	GLuint sprite = NULL; //texture of game object
	ENTITY_TYPE entityType;

public:

	GameObject(); //constructor
	GameObject(Vector2 _pos); //constructor with position
	GameObject(Vector2 _pos, float _size); //constructor with position and size
	~GameObject();//destructor

	float GetSize();
	Vector2 GetPosition(); //returns position
	ENTITY_TYPE GetEntityType(); //returns position
	virtual void Render(); //draws the game object (overridable)
	virtual void Update();// updates the game object's logic (overridable)
	virtual void OnCollisionEnter(GameObject& goRef);//

};

#endif // !GAMEOBJECT_H
