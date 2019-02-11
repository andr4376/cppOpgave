#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Globals.h"
#include <SOIL.h>
#include <GLFW\glfw3.h>
#include "Vector2.h"


class GameObject
{
private:
	GLuint sprite; //texture of game object

protected:
	Vector2 position; //it's position in a 2d space
	float size = 1;

public:

	GameObject(); //constructor
	GameObject(Vector2 _pos); //constructor with position
	GameObject(Vector2 _pos, float _size); //constructor with position and size

	~GameObject();//destructor

	Vector2 GetPosition(); //returns position
	virtual void Render(); //draws the game object (overridable)
	virtual void Update();// updates the game object's logic (overridable)
};

#endif // !GAMEOBJECT_H
